/*H**********************************************************************
* FILENAME :	rot13_v1.c
*
* DESCRIPTION :
*       ROT13 cipher implementation
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

/* Performs encryption or decryption via the rot13 cipher */
void rot13(int mode, char fname[]) {
	FILE *fp_in = fopen(fname, "r");
	FILE *fp_out = fopen(mode ? "ciphertext.txt" : "plaintext2.txt", "w");
	char buff[255];
	int i;
	for (i = 0; i < 255; i++)
		buff[i] = '\0';
	while (fgets(buff, 255, fp_in) != NULL) {
		for (i = 0; i < 255 && buff[i] != '\0'; i++) {
			if ((buff[i] >= 'a' && buff[i] <= 'm') ||
				(buff[i] >= 'A' && buff[i] <= 'M')) {
				buff[i] += 13;
			} else if ((buff[i] > 'm' && buff[i] <= 'z') ||
				(buff[i] > 'M' && buff[i] <= 'Z')) {
				buff[i] -= 13;
			}
		}
		fputs(buff, fp_out);
	};
	fclose(fp_in);
	fclose(fp_out);
	printf("\n%s\n", mode ? "Encrypted" : "Decrypted");
}

/* Driver Function */
int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("%s\n", "ERROR: ./rot13_vX.exe e|d 'textfile'");
	} else {
		if (strcmp(argv[1], "e") != 0 && strcmp(argv[1], "d") != 0) {
			printf("%s\n", "ERROR: ./rot13_vX.exe e|d 'textfile'");
		} else {
			rot13(!strcmp(argv[1], "e") ? 1 : 0, argv[2]);
		}
	}
	exit(0);
}