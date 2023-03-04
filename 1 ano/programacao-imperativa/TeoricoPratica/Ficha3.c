#include <stdio.h>

// 1)
// a)
int umA() {
	int x[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int *y, *z, i; // y -> lugar na memoria || z -> lugar na memória
	y = x;
	z = x+3;
	for (i = 0; i < 5; i++) {
		printf("%d %d %d\n",x[i], *y, *z);
		y++;
		z += 2;
	}
	return 0;
}
// 



// 2)
void swapM(int *x, int *y) {
	int temp;
	temp = x;
	*x = y;
	*y = temp;
}


int main() {
	// umA();
	int x = 3, y = 5;

	swapM(&x, &y);

	return 0;
}

