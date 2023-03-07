#include <stdio.h>
#include <string.h> 

int main() {
	int N = 0;
	char linha[200];
	char* token;

	int index = 0;
	char* arrayParaOrdenar[200];

	int maior = 0;

	if (scanf("%d", &N) != 1) return 1;

	for (int i = 0; i < N + 1 ; i++) { // linhas

		fgets(linha,200,stdin); 

		token = strtok(linha, " ");

		while (token != NULL) {

			arrayParaOrdenar[index++] = token;

			token = strtok(NULL, " ");

		}

		for (int i = 0; i < 3; i++) {
			printf("%s",arrayParaOrdenar[i]);
		}
		
		memset(linha,0,strlen(linha));

	}	

	return 0;
}