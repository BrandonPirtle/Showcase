/*H**********************************************************************
* FILENAME :	collect.c
*
* DESCRIPTION :
*       Exhibits MPI collective operations
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
	s[len] = '\0';
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
	char *elmnts;   /* The local elements array */
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
	nlocal = n / npes; /* Computer the number of local elements */
	leftovers = n % nlocal; /* Computer the remainder from nlocal */

	/* Allocate memory for the various arrays */
	string = (char *)malloc(sizeof(char) * n);
	if (string == NULL) {
		printf("ERROR: malloc of size %d failed!\n", n);
		exit(1);
	}
	elmnts = (char *)malloc(sizeof(char) * nlocal);
	if (elmnts == NULL) {
		printf("ERROR: malloc of size %d failed!\n", nlocal);
		exit(1);
	}

	if (!myrank) { /* If process 0, perform 'master' duties */
		gen_random(string, n); /* Generate the random string to be sorted */
		printf("Proc 0 made a random string: %s\n", string);
	}
	/* Distribute data from 'master' to all processes */
	MPI_Scatter(string, nlocal, MPI_CHAR, elmnts, nlocal,
		MPI_CHAR, 0, MPI_COMM_WORLD);
	printf("Proc %d received a string from proc 0: %s\n",
		myrank, elmnts);
	qsort(elmnts, nlocal, sizeof(char), cmpfunc);
	printf("Proc %d sorted its string: %s\n", myrank, elmnts);
	/* Retrieve data from all processes to 'master' */
	MPI_Gather(elmnts, nlocal, MPI_CHAR, string, nlocal,
		MPI_CHAR, 0, MPI_COMM_WORLD);
	if (!myrank) {
		qsort(string, n, sizeof(char), cmpfunc);
		printf("Proc 0 sorted the final string: %s\n", string);
	}

	/* Release memory for the various arrays */
	free(string); free(elmnts);

	MPI_Finalize();
	exit(0);
}
