/*H**********************************************************************
* FILENAME :	affine_v1.c
*
* DESCRIPTION :
*       Affine cipher implementation
*
* NOTES :
*       #####
*       CS 6313 Data Security Project
* 
* AUTHOR :    Brandon Pirtle        START DATE :    30 Oct 17
*
*H*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Returns the multiplicative inverse */
int mult_inverse(int a, int b) {
	a = a % b;
	int i;
	for (i = 1; i < b; i++)
		if ((a * i) % b == 1)
			return i;
}

/* Performs encryption or decryption via the affine cipher
	e: E(x) = (a * (x - ref) + b) mod m
	d: D(x) = a^-1 * ((x + ref)- b) mod m */
void affine(int mode, int a, int b, char fname[]) {
	FILE *fp_in = fopen(fname, "r");
	FILE *fp_out = fopen(mode ? "ciphertext.txt" : "plaintext2.txt", "w");
	if (!mode)
		a = mult_inverse(a, 26);
	char buff[255];
	int i;
	for (i = 0; i < 255; i++)
		buff[i] = '\0';
	while (fgets(buff, 255, fp_in) != NULL) {
		for (i = 0; i < 255 && buff[i] != '\0'; i++)
			buff[i] = (char)(((mode ? ((a * (buff[i] - 'A')) + b)
				: (a * ((buff[i] + 'A') - b))) % 26) + 65);
		fputs(buff, fp_out);
	};
	fclose(fp_in);
	fclose(fp_out);
	printf("\n%s\n", mode ? "Encrypted" : "Decrypted");
}

/* Driver Function */
int main(int argc, char *argv[]) {
	if (argc != 5) {
		printf("%s\n", "ERROR: ./affine_vX.exe e|d 'textfile' a b");
	} else {
		if (strcmp(argv[1], "e") != 0 && strcmp(argv[1], "d") != 0) {
			printf("%s\n", "ERROR: ./affine_vX.exe e|d 'textfile' a b");
		} else {
			char *ptr;
			affine(!strcmp(argv[1], "e") ? 1 : 0,
				strtol(argv[3], &ptr, 10), strtol(argv[4], &ptr, 10), argv[2]);
		}
	}
	exit(0);
}