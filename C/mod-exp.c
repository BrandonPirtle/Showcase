/*H**********************************************************************
* FILENAME :	mod-exp.c
*
* DESCRIPTION :
*       Modular exponentiation algorithm
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

int int_to_bin_int(int a)
{
	return (a == 0 || a == 1 ? a : ((a % 2) + 10 * int_to_bin_int(a / 2)));
}

int num_digits(int a)
{
	int x = 0;
	while (a != 0)
	{
		a /= 10;
		x++;
	}
	return x;
}

void bin_int_to_array(int *array, int x, int a)
{
	if (x != 0)
	{
		while (a != 0)
		{
			array[x - 1] = a % 10;
			a /= 10;
			x--;
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("%s\n", "ERROR: only 3 parameters allowed");
	}
	else
	{
		char *ptr;
		int a = strtol(argv[1], &ptr, 10);
		int b = strtol(argv[2], &ptr, 10);
		int n = strtol(argv[3], &ptr, 10);
		if (a < 1 || b < 1)
		{
			printf("%s\n", "ERROR: only positive integers allowed");
		}
		else
		{
			int d = 1;
			int bin_int = int_to_bin_int(b);
			printf("bin_int: %d\n", bin_int);
			int SIZE = num_digits(bin_int);
			printf("SIZE: %d\n", SIZE);
			int bin[SIZE];
			bin_int_to_array(bin, SIZE, bin_int);
			int k, i;
			printf("bin: ");
			for (i = 0; i < SIZE; i++)
			{
				printf("%d", bin[i]);
			}
			printf("\n");
			for (i = SIZE; i >= 0; i--)
			{
				if (bin[i] == 1)
				{
					k = SIZE - i;
				}
			}
			printf("k: %d\n", k);
			for (i = k; i > 0; i--)
			{
				d = d * d % n;
				if (bin[k - i] == 1)
				{
					d = (d * a) % n;
				}
			}
			printf("GCD: %d\n", d);
		}
	}

	exit(0);
}