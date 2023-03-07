#include <stdio.h>
#include <string.h> 

int main() {
	int n;
	int K = 0;
	int atual = 0;
	int index = 0;

	int maior = 0;

	if (scanf("%d", &n) != 1) return 1;

	int arrayMaiores[n];

	for (int i = 0; i < n; i++) { // linhas
		if (scanf("%d", &K) != 1) return 1;

		for (int j = 0; j < K; j++) {

			if (scanf("%d", &atual) != 1) return 1;

			if (atual > maior) {
				index++;
				maior = atual;
			}
		}
		arrayMaiores[i] = index;
		maior = 0;
		index = 0;
	}	

	for (int x = 0; x < n; x++) {
		printf("%d\n", arrayMaiores[x]);
	}

	return 0;
}