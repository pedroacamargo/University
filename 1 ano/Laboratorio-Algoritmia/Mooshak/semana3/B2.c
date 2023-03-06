#include <stdio.h>
#include <string.h>

// Essa é a certa

// 7 8 9
// 4 5 6
// 1 2 3

int main() {
	int N = 0;
	char comando[25];
	char r[100];

	int x = 0;
	int y = 0;

	if (scanf("%d",&N) != 1) return 1;

	for (int i = 0; i < N; i++) {
		if (scanf("%s", comando) != 1) return 1;

		for (int j = 0; j < (int) strlen(comando); j++) {
			if(comando[j] == 'C') {
				if (y < 1) {
					y += 1;
				}
			} else if (comando[j] == 'B') {
				if (y > -1) {
					y--;
				}
			} else if (comando[j] == 'D') {
				if (x < 1) {
					x++;
				}
			} else if (comando[j] == 'E') {
				if (x > -1) {
					x--;
				}
			}
		}

		if (x == 0 && y == 0) {
			r[i] = 5;
		} else if (x == 1 && y == 0) {
			r[i] = 6;
		} else if (x == -1 && y == 0) {
			r[i] = 4;
		} else if (x == 1 && y == 1) {
			r[i] = 9;
		} else if (x == 0 && y == 1) {
			r[i] = 8;
		} else if (x == -1 && y == 1) {
			r[i] = 7;
		} else if (x == 0 && y == -1) {
			r[i] = 2;
		} else if (x == 1 && y == -1) {
			r[i] = 3;
		} else if (x == -1 && y == -1) {
			r[i] = 1;
		}
	}

	
	for (int i = 0; i < N;i++) {
		printf("%d",r[i]);
	}

	printf("\n");
	return 0;
}