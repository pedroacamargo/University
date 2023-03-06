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
			if (choices[j] == 'C') {
				if(value < 7) {
					value += 3;
				}
			} else if (choices[j] == 'B') {
				if (value > 3) {
					value -= 3;
				}
			} else if (choices[j] == 'D') {
				if (value != 3 || value != 6 || value != 9) {
					value++;
				}
			} else {
				if (value != 1 || value != 4 || value != 7) {
					value--;
				}
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