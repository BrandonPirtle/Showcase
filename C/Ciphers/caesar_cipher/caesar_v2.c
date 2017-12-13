/*H**********************************************************************
* FILENAME :	caesar_v2.c
*
* DESCRIPTION :
*       Caesar cipher implementation
*
* NOTES :
*       #####
*       CS 6313 Data Security Project
* 
* AUTHOR :    Brandon Pirtle        START DATE :    23 Oct 17
*
*H*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Returns integer key from textfile */
int get_key(char fname[]) {
	char *ptr, buff[10];
	FILE *fp = fopen(fname, "r");
	int key = strtol(fgets(buff, 10, fp), &ptr, 10);
	fclose(fp);
	return key;
}

/* Performs encryption or decryption via the caesar cipher
	e: En(x) = (x + n) mod 26
	d: Dn(x) = (x - n) mod 26 */
void caesar(int mode, int key, char fname[]) {
	FILE *fp_in = fopen(fname, "r");
	FILE *fp_out = fopen(mode ? "ciphertext.txt" : "plaintext2.txt", "w");
	char buff[255];
	int i, j;
	for (i = 0; i < 255; i++)
		buff[i] = '\0';
	while (fgets(buff, 255, fp_in) != NULL) {
		for (i = 0; i < 255 && buff[i] != '\0'; i++)
			for (j = 0; j <= key; j++)
				mode ? buff[i]++ : buff[i]--;
		fputs(buff, fp_out);
	}
	fclose(fp_in);
	fclose(fp_out);
	printf("\n%s\n", mode ? "Encrypted" : "Decrypted");
}

/* Driver Function */
int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("%s\n", "ERROR: ./caesar_vX.exe e|d 'textfile' 'keyfile'");
	} else {
		if (strcmp(argv[1], "e") != 0 && strcmp(argv[1], "d") != 0) {
			printf("%s\n", "ERROR: ./caesar_vX.exe e|d 'textfile' 'keyfile'");
		} else {
			caesar(!strcmp(argv[1], "e") ? 1 : 0, get_key(argv[3]), argv[2]);
		}
	}
	exit(0);
}