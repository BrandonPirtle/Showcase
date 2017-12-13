/*H**********************************************************************
* FILENAME :	prime.c
*
* DESCRIPTION :
*       Miller Rabin Algorithm for primality testing
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
#include <math.h>

int modular_exponentiation(int b, int e, int m)
{
	int x = 1;
	int p = b % m;
	while (e != 0)
	{
		if (e & 1)
		{
			x = (x * p) % m;
			e -= 1;
		}
		p = (p * p) % m;
		e /= 2;
	}
	return x;
}

int main(int argc, char *argv[])
{
	// Check for correct amount of parameters
	if (argc != 3)
	{
		printf("ERROR: only 2 parameters allowed\n");
	}
	else
	{
		// convert command line args to ints
		char *ptr;
		int a = strtol(argv[1], &ptr, 10);
		int n = strtol(argv[2], &ptr, 10);
		printf("a = %d n = %d\n", a, n);
		// if n is even or a multiple of 5, then output composite directly
		if (n % 2 == 0 || n % 5 == 0)
		{
			printf("composite\n");
			exit(0);
		}
		else
		{
			// find k by dividing n by 2 repeatedly, as long as n is even
			int k = 0;
			int m = n - 1; /* temp n for editing */
			while (m % 2 == 0)
			{
				m /= 2;
				k++;
			}
			// q = (n - 1) / 2^k
			int q = (n - 1) / (int)pow(2, k);
			printf("k = %d q = %d\n", k, q);
			int num1 = modular_exponentiation(a, q, n);
			printf("num1 = %d\n", num1);
			if (num1 == 1)
			{
				printf("maybe prime\n");
				exit(0);
			}
			else
			{
				int i;
				for (i = 0; i < k; i++)
				{
					int num2 = modular_exponentiation(a, (int)pow(2,i) * q, n);
					printf("num2 = %d\n", num2);
					if (num2 == n - 1)
					{
						printf("maybe prime\n");
						exit(0);
					}
				}
				printf("composite\n");
			}
		}
	}

	exit(0);
}