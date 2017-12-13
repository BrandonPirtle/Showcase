/*H**********************************************************************
* FILENAME :	atbash_v1.c
*
* DESCRIPTION :
*       Atbash cipher implementation
*
* NOTES :
*       #####
* 
* AUTHOR :    Brandon Pirtle        START DATE :    22 Nov 17
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

/* Performs encryption or decryption via the atbash cipher
	e: E(x) = ((a * (x - ref) + 25) mod 26) + 65
	d: D(X) = ((a * (x + ref) - 25) mod 26) + 65 */
void atbash(int mode, char fname[]) {
	FILE *fp_in = fopen(fname, "r");
	FILE *fp_out = fopen(mode ? "ciphertext.txt" : "plaintext2.txt", "w");
	int a = 25;
	if (!mode)
		a = mult_inverse(a, 26);
	char buff[255];
	int i;
	for (i = 0; i < 255; i++)
		buff[i] = '\0';
	while (fgets(buff, 255, fp_in) != NULL) {
		for (i = 0; i < 255 && buff[i] != '\0'; i++)
			buff[i] = (char)(((mode ? ((a * (buff[i] - 'A')) + 25)
				: (a * ((buff[i] + 'A') - 25))) % 26) + 65);
		fputs(buff, fp_out);
	};
	fclose(fp_in);
	fclose(fp_out);
	printf("\n%s\n", mode ? "Encrypted" : "Decrypted");
}

/* Driver Function */
int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("%s\n", "ERROR: ./atbash_vX.exe e|d 'textfile'");
	} else {
		if (strcmp(argv[1], "e") != 0 && strcmp(argv[1], "d") != 0) {
			printf("%s\n", "ERROR: ./atbash_vX.exe e|d 'textfile'");
		} else {
			atbash(!strcmp(argv[1], "e") ? 1 : 0, argv[2]);
		}
	}
	exit(0);
}