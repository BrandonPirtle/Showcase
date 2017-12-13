/*H**********************************************************************
* FILENAME :	p2p.c
*
* DESCRIPTION :
*       Exhibits MPI point-to-point communication primitives
*
* NOTES :
*       Execute using mpiexec
* 
* AUTHOR :    Brandon Pirtle        START DATE :    30 Oct 17
*									EDIT  DATE :	13 Dec 17
*
*H*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gen_random(char *s, const int len) {
	static const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;
	time_t t;
	srand((unsigned) time(&t));
	for (i = 0; i < len; i++)
		s[i] = chars[rand() % (sizeof(chars) - 1)];
	s[len] = 0;
}

int cmpfunc(const void *a, const void *b) {
	return (*(const char *)a - *(const char *)b);
}

int main(int argc, char *argv[]) {
	int  n;         /* The total number of elements to be sorted */
	int  npes;      /* The total number of processes */
	int  myrank;    /* The rank of the calling process */
	char *ptr;      /* The pointer used for strol() */
	char *string;   /* The array that stores the original random string */
	int  nlocal;    /* The length of the local elements array */
	char *elmnts[npes-1]; /* The local elements array */
	int  leftovers; /* The index of the start of the elements that
						are not distributed to 'slave' processes */
	int  i, j;
	MPI_Status status;

	/* Initialize MPI and get system information */
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &npes);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	printf("Process %d of %d checking in.\n", myrank, npes);

	n = strtol(argv[1], &ptr, 10); /* Pull in length from command line */
	nlocal = n / (npes - 1); /* Computer the number of local elements */
	leftovers = n % nlocal; /* Computer the remainder from nlocal */

	/* Allocate memory for the various arrays */
	string = (char *)malloc(sizeof(char) * n);
	if (string == NULL) {
		printf("ERROR: malloc of size %d failed!\n", n);
		exit(1);
	}
	for (i = 0; i < npes - 1; i++) {
		elmnts[i] = (char *)malloc(sizeof(char) * nlocal);
		if (elmnts[i] == NULL) {
			printf("ERROR: malloc of size %d failed!\n", nlocal);
			exit(1);
		}
	}

	if (!myrank) { /* If process 0, perform 'master' duties */
		gen_random(string, n); /* Generate the random string to be sorted */
		printf("Proc 0 made a random string: %s\n", string);
		for (i = 1; i < npes; i++) {
			for (j = 0; j < nlocal; j++) /* Create substrings */
				elmnts[i-1][j] = string[j + ((i - 1) * nlocal)];
			elmnts[i-1][nlocal] = '\0';
			printf("Proc 0 made proc %d a string: %s\n", i, elmnts[i-1]);
			/* Send new substring to a 'slave' process */
			MPI_Send(elmnts[i-1], nlocal, MPI_INT, i, 1, MPI_COMM_WORLD);
		}
		printf("Proc 0 is waiting at first barrier\n");
		MPI_Barrier(MPI_COMM_WORLD); /* Wait for 'slaves' to do work */
		for (i = 1; i < npes; i++) {
			/* Receive sorted substring from 'slave' processes */
			MPI_Recv(elmnts[i-1], nlocal, MPI_INT, i, 1,
				MPI_COMM_WORLD, &status);
			printf("Proc 0 received a string from proc %d: %s\n",
				i, elmnts[i-1]);
		}
		/* Merge the sorted substrings and sort */
		for (i = 0; i < npes - 1; i++)
			for (j = 0; j < nlocal; j++)
				string[(i * nlocal) + j] = elmnts[i][j];
		qsort(string, n, sizeof(char), cmpfunc);
		printf("Proc 0 sorted the final string: %s\n", string);
	} else { /* If not process 0, perform 'slave' duties */
		/* Receive substring from 'master' process */
		MPI_Recv(elmnts[myrank-1], nlocal, MPI_INT, 0, 1,
			MPI_COMM_WORLD, &status);
		printf("Proc %d received a string from proc 0: %s\n",
			myrank, elmnts[myrank-1]);
		/* Sort the substring */
		qsort(elmnts[myrank-1], nlocal, sizeof(char), cmpfunc);
		printf("Proc %d sorted its string: %s\n", myrank, elmnts[myrank-1]);
		/* Send sorted substring to 'master' process */
		MPI_Send(elmnts[myrank-1], nlocal, MPI_INT, 0, 1, MPI_COMM_WORLD);
		printf("Proc %d is waiting at first barrier\n", myrank);
		/* Wait for 'master' process to receive all substrings */
		MPI_Barrier(MPI_COMM_WORLD);
	}

	/* Wait for all processes */
	printf("Proc %d is waiting at second barrier\n", myrank);
	MPI_Barrier(MPI_COMM_WORLD);

	/* Release memory for the various arrays */
	free(string);
	for (i = 0; i < npes - 1; i++)
		free(elmnts[i]);

	MPI_Finalize();
	exit(0);
}
