#include <stdio.h>
#include <string.h>

// strlen(str) -> string length
// printf("%c\n", n[2]);

int main() {
	int charAtual = 1;
	char arrayDesordenado[1000] = "";
	char arrayOrdenar[1000] = "";

	char posicao[8]; // 31254

	if (scanf("%s", posicao) != 1) return 1;

	char msg[1000];  


	if (scanf("%s", msg) != 1) return 1;

	int lengthPosicao = strlen(posicao);
	int lengthMsg = strlen(msg);

	// criptography the msg
	for (int i = 1; i <= lengthPosicao; i++) { // get a char in each group

		for (int j = 0; j <= lengthMsg; j++) { 

			if (i == charAtual) {
				arrayDesordenado[strlen(arrayDesordenado)] = msg[j];
			}

			charAtual++;

			// reset the index of each group
			if (charAtual > lengthPosicao) {
				charAtual = 1;
			}

		}

		strcat(arrayOrdenar, arrayDesordenado);
		arrayOrdenar[strlen(arrayOrdenar)] = ' ';

		// clear the array for the next loop
		memset(arrayDesordenado,0,strlen(arrayDesordenado));

		charAtual = 1;
	}	

	char* token;
	char* array[1000];


	int order = 0;


	int i = 0;
	token = strtok(arrayOrdenar, " ");

	// create an array with each "word"
	while(token != NULL) {
		array[i++] = token;
		token = strtok(NULL, " ");
	}

	for (int i = 0; i < lengthPosicao;i++) {
		order = (posicao[i] - '0') - 1;
		printf("%s",array[order]);
	}
	printf("\n");

	return 0;
}