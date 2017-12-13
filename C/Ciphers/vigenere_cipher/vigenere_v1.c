/*H**********************************************************************
* FILENAME :	vigenere_v1.c
*
* DESCRIPTION :
*       Vigenere cipher implementation
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
#include <ctype.h>

/* Retrieves character array key from textfile */
void get_key(char buff[], char fname[]) {
	FILE *fp = fopen(fname, "r");
	fgets(buff, 255, fp);
	fclose(fp);
}

/* Performs encryption or decryption via the vigenere cipher
	C[i] = E[k](M[i]) = (M[i] + K[i * mod m]) mod l
	M[i] = D[k](C[i]) = (C[i] - K[i * mod m]) mod l	*/
void vigenere(int mode, char fname[], char keyfile[]) {
	FILE *fp_in = fopen(fname, "r");
	FILE *fp_out = fopen(mode ? "ciphertext.txt" : "plaintext2.txt", "w");
	char buff[255], key[255];
	get_key(key, keyfile);
	int key_len = strlen(key);
	int i, j, value;
	for (i = 0; i < 255; i++)
		buff[i] = '\0';
	while (fgets(buff, 255, fp_in) != NULL) {
		for (i = 0, j = 0; i < 255 && buff[i] != '\0'; i++) {
			if (isalpha(buff[i])) {
				char key_ref = isupper(key[j % key_len]) ? 'A' : 'a';
				char ref = isupper(buff[i]) ? 'A' : 'a';
				if (mode) {
					buff[i] = ((buff[i] - ref + (key[j % key_len] - key_ref)) 
						% 26) + ref;
				} else {
					value = buff[i] - ref - (key[j % key_len] - key_ref);
					if (value < 0)
						value += 26;
					buff[i] = (value % 26) + ref;
				}
				j++;
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
	if (argc != 4) {
		printf("%s\n", "ERROR: ./vigenere_vX.exe e|d 'textfile' 'keyfile'");
	} else {
		if (strcmp(argv[1], "e") != 0 && strcmp(argv[1], "d") != 0) {
			printf("%s\n","ERROR: ./vigenere_vX.exe e|d 'textfile' 'keyfile'");
		} else {
			vigenere(!strcmp(argv[1], "e") ? 1 : 0, argv[2], argv[3]);
		}
	}
	exit(0);
}