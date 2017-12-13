/*H**********************************************************************
* FILENAME :	caesar_v1.c
*
* DESCRIPTION :
*       Caesar cipher implementation
*
* NOTES :
*       #####
* 
* AUTHOR :    Brandon Pirtle        START DATE :    22 Sep 17
*
*H*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Returns integer key from textfile */
int get_key(char fname[])
{
	char *ptr;
	char buff[10];
	FILE *fp = fopen(fname, "r");
	int key = strtol(fgets(buff, 10, fp), &ptr, 10);
	fclose(fp);
	// printf("%d\n", key);
}

/* Performs encryption via the caesar cipher */
void encipher(int key, char fname[])
{
	FILE *fp_in = fopen(fname, "r");
	FILE *fp_out = fopen("ciphertext.txt", "w");
	char buff[255];
	int i, j;
	for (i = 0; i < 255; i++)
	{
		buff[i] = '\0';
	}
	while (fgets(buff, 255, fp_in) != NULL)
	{
		for (i = 0; i < 255 && buff[i] != '\0'; i++)
		{
			for (j = 0; j <= key; j++)
			{
				buff[i]++;
			}
		}
		// printf("%s", buff);
		fputs(buff, fp_out);
	};
	printf("\n");
	fclose(fp_in);
	fclose(fp_out);
	printf("%s\n", "Encrypted");
}

/* Performs decryption via the caesar cipher */
void decipher(int key, char fname[])
{
	FILE *fp_in = fopen(fname, "r");
	FILE *fp_out = fopen("plaintext2.txt", "w");
	char buff[255];
	int i, j;
	for (i = 0; i < 255; i++)
	{
		buff[i] = '\0';
	}
	while (fgets(buff, 255, fp_in) != NULL)
	{
		for (i = 0; i < 255 && buff[i] != '\0'; i++)
		{
			for (j = 0; j <= key; j++)
			{
				buff[i]--;
			}
		}
		// printf("%s", buff);
		fputs(buff, fp_out);
	};
	printf("\n");
	fclose(fp_in);
	fclose(fp_out);
	printf("%s\n", "Decripted");
}

/* Driver Function */
int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("%s\n", "ERROR");
	}
	else
	{
		if (strcmp(argv[1], "e") != 0 && strcmp(argv[1], "d") != 0)
		{
			printf("%s\n", "ERROR");
		}
		else
		{
			int key = get_key(argv[3]);
			if (strcmp(argv[1], "e") == 0)
			{
				encipher(key, argv[2]);
			}
			else // is known to be d
			{
				decipher(key, argv[2]);
			}
		}
	}

	exit(0);
}