/*H**********************************************************************
* FILENAME :	thread_sort.c
*
* DESCRIPTION :
*       Exhibits threads and their use for sorting
*
* NOTES :
*       Tested with: ./thread_sort 30
* 
* AUTHOR :    Brandon Pirtle        START DATE :    20 Nov 17
*
*H*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

static int NUM_THREADS = 4;

/* Structure that holds arguments for threads */
struct thread_args {
    int id;
    char *elmnts;
    int length;
};

/* Generates a random string of capital letters */
void gen_random(char *s, const int len) {
	static const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;
	time_t t;
	srand((unsigned) time(&t));
	for (i = 0; i < len; i++)
		s[i] = chars[rand() % (sizeof(chars) - 1)];
	s[len] = 0;
}

/* The compare function to be used with qsort() */
int cmpfunc(const void *a, const void *b) {
	return (*(const char *)a - *(const char *)b);
}

/* Driver sort function for each thread */
void Sort(void *arguments) {
	struct thread_args *args = arguments;
	printf("Thread %d: checking in\n", args -> id);
	qsort(args -> elmnts, args -> length, sizeof(char), cmpfunc);
	printf("Thread %d: sorted string: %s\n", args -> id, args -> elmnts);
	printf("Thread %d: checking out\n", args -> id);
	pthread_exit(NULL);
}

/* Driver Function */
int main(int argc, char *argv[]) {
	char *ptr;                          /* Pointer used for strtol() */
	int n = strtol(argv[1], &ptr, 10);  /* Length of string */
	int nlocal = (n / NUM_THREADS) + 1; /* Length of local strings */
	int leftover = n % NUM_THREADS;     /* Possible emptiness in last elmnts */
	char *string;                       /* Holds original random string */
	char *elmnts[NUM_THREADS];          /* Holds local portitions of string */
	pthread_t threads[NUM_THREADS];     /* Thread handlers */
	int rc;                             /* Thread return code */
	int i, j;                           /* Loop indices */
	struct thread_args args[NUM_THREADS]; /* Arguments for threads */

	/* Allocate memory for the various arrays */
	string = (char *)malloc(sizeof(char) * n);
	if (string == NULL) {
		printf("ERROR: malloc of size %d failed\n", n);
		exit(1);
	}
	for (i = 0; i < NUM_THREADS; i++) {
		elmnts[i] = (char *)malloc(sizeof(char) * nlocal);
		if (elmnts[i] == NULL) {
			printf("ERROR: malloc of size %d failed\n", nlocal);
			exit(1);
		}
	}

	/* Generate the random string to be sorted */
	gen_random(string, n);
	printf("Master: new string: %s\n", string);
	/* Divide string into parts for threads */
	for (i = 0; i < NUM_THREADS; i++) {
		for (j = 0; j < nlocal; j++) /* Create substrings */
			elmnts[i][j] = string[j + (i * nlocal)];
		elmnts[i][nlocal] = '\0';
		printf("Master: for Thread %d: %s\n", i, elmnts[i]);
	}

	/* Create theads */
	for (i = 0; i < NUM_THREADS; i++) {
		printf("Master: creating Thread %d\n", i);
		/* Update the new thread's argument structure */
		args[i].id = i;
		args[i].elmnts = elmnts[i];
		args[i].length = (i != (NUM_THREADS - 1)) ? nlocal : nlocal - leftover;
		/* Create the new thread */
		rc = pthread_create(&threads[i], NULL, (void *)Sort, (void *)&args[i]);
		if (rc) {
			printf("ERROR: return code from pthread_create() is %d\n", rc);
			exit(1);
		}
	}

	/* Wait for threads */
	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	/* Merge the sorted substrings and sort */
	for (i = 0; i < NUM_THREADS; i++)
		for (j = 0; j < (i != (NUM_THREADS-1) ? nlocal : nlocal-leftover); j++)
			string[(i * nlocal) + j] = args[i].elmnts[j];
	qsort(string, n, sizeof(char), cmpfunc);
	printf("Master: sorted string: %s\n", string);

	/* Release memory for the various arrays */
	free(string);
	for (i = 0; i < NUM_THREADS; i++)
		free(elmnts[i]);

	pthread_exit(NULL);
	exit(0);
}
