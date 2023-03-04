#include <stdio.h>

// /home/mutante/Programming/University/1 ano/programacao-imperativa/ByMyOwn

int main() {
	FILE *pF = fopen("/home/mutante/Programming/University/1 ano/programacao-imperativa/ByMyOwn/poem.txt", "r");

	// buffer
	char buffer[255];

	if (pF == NULL) {
		printf("Unable to open file!\n");
	} else {
		while (fgets(buffer, 255,pF) != NULL) {
			printf("%s",buffer);
		}		
	}
	fclose(pF);
	return 0;
}