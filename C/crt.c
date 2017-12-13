/*H**********************************************************************
* FILENAME :	crt.c
*
* DESCRIPTION :
*       Chinese Remainder Theorem
*
* NOTES :
*       #####
* 
* AUTHOR :    Brandon Pirtle        START DATE :    20 Sep 17
*									EDIT  DATE :	13 Dec 17
*
*H*/

#include <stdio.h>
#include <stdlib.h>

int mult_inverse(int a, int b)
{
	a = a % b;
	int i;
	for (i = 1; i < b; i++)
	{
		if ((a * i) % b == 1)
		{
			return i;
		}
	}
}

int main(int argc, char *argv[])
{
	// Check for existence of parameters
	if (argc == 1)
	{
		printf("ERROR: list parameter A and parameters m[i]\n");
	}
	else if (argc == 2)
	{
		printf("ERROR: list parameters m[i]\n");
	}
	else
	{
		// convert command line args to ints
		char *ptr;
		int A = strtol(argv[1], &ptr, 10);
		printf("A = %d\n", A);
		int B = 0; /* Recovered A */
		int k = argc-2; /* length of arrays */
		int i;
		int M = 1;
		int m[k];
		int a[k];
		int N[k];
		int c[k];
		for (i = 0; i < k; i++)
		{
			m[i] = strtol(argv[i+2], &ptr, 10);
			printf("m[%d] = %d\n", i, m[i]);
			a[i] = A % m[i];
			printf("a[%d] = %d\n", i, a[i]);
			M *= m[i];
		}
		printf("M = %d\n", M);
		for (i = 0; i < k; i++)
		{
			N[i] = M / m[i];
			printf("N[%d] = %d\n", i, N[i]);
			c[i] = N[i] * mult_inverse(N[i], m[i]);
			printf("c[%d] = %d\n", i, c[i]);
			B += (a[i] * c[i]);
		}
		B %= M;
		printf("B = %d\n", B);
	}

	exit(0);
}