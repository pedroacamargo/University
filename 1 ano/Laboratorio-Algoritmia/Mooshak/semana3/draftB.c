#include <stdio.h>
#include <string.h>

/*
	7 8 9
	4 5 6
	1 2 3
*/

int main() {

	int value = 5;
	int N = 0;
	char choices[100];

	if (scanf("%d",&N) != 1) return 1;

	int result[N]; 

	for (int i = 0; i < N; i++) {
		if (scanf("%s",choices) != 1) return 1;
		int sizeChoices = sizeof(choices)/sizeof(choices[0]);

		for (int j = 0; j < sizeChoices - 1; j++) {
			switch (choices[j]) {
				case 'C':
					if (value < 7) {
						value += 3;
					}
					break;
				case 'B':
					if (value > 3) {
						value -= 3;
						break;
					}
					break;
				case 'D':
					if (value == 3) {
						break;
					} else if (value == 6) {
						break;
					} else if (value == 9) {
						break;
					} else {
						value++;
						break;
					}
				case 'E':
					if (value == 1) {
						break;
					} else if (value == 4) {
						break;
					} else if (value == 7) {
						break;
					} else {
						value--;
						break;
					}
				default:
					break;
			}

		}
		result[i] = value;
	}

	int sizeResult = sizeof(result)/sizeof(result[0]);

	for (int i = 0; i < sizeResult;i++) {
		printf("%d", result[i]);
	}

	printf("\n");

	return 0;
}