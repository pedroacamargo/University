#include <stdio.h>

int main() {
	/*
	FILE *pF = fopen("test.txt", "a");

	fprintf(pF, "Spongebob Squarepants\n");

	fclose(pF);
	*/

	if (remove("test.txt") == 0) {
		printf("That file was deleted successfully!\n");
	} else {
		printf("That file was NOT deleted!\n");
	}
	return 0;
}