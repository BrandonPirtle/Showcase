/*H**********************************************************************
* FILENAME :	e-euclid.c
*
* DESCRIPTION :
*       Extended Euclidean algorithm for GCD and inverse
*
* NOTES :
*       #####
* 
* AUTHOR :    Brandon Pirtle        START DATE :    13 Sep 17
*									EDIT  DATE :	13 Dec 17
*
*H*/

#include <stdio.h>
#include <stdlib.h>

int euclid(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	else
	{
		return euclid(b, a % b);
	}
}

int extended_euclid(int a, int b, int *x, int *y)
{
	if (a == 0)
	{
		*x = 0;
		*y = 1;
		return b;
	}
	int x1, y1;
	int gcd = extended_euclid(b % a, a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;
	printf("%d %d\n", *x, *y);
	return gcd;
}

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
	if (argc != 3)
	{
		printf("%s\n", "ERROR: only 2 parameters allowed");
	}
	else
	{
		char *ptr;
		int a = strtol(argv[1], &ptr, 10);
		int b = strtol(argv[2], &ptr, 10);
		if (a < 1 || b < 1)
		{
			printf("%s\n", "ERROR: only positive integers allowed");
		}
		else
		{
			int x, y;
			int c = extended_euclid(a, b, &x, &y);
			if (c == 1)
			{
				c = mult_inverse(a, b);
				printf("%s%d\n", "INV = ", c);
			}
			else
			{
				printf("%s%d\n", "GCD = ", c);
			}
		}
	}

	exit(0);
}