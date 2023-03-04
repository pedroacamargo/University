#include <stdio.h>

int main() {
	// BITWISE OPERATORS = special operators used in bit level programming
	// 					   (knowing binary is important for this topic)

	// & = AND --> both need to be 1
	// | = OR --> anyone needs to be 1
	// ^ = XOR -> exclusive or --> only 1 has to be 1
	// << = left shift --> shitfs one character to the left
	// >> = right shift --> the same but to the right

	int x = 6; // 6 = 00000110
	int y = 12;// 12= 00001100
	int z = 0; // 0 = 00000000

	z = x & y; // z = 00000100 = 4
	printf("AND = %d\n", z);

	z = x | y;
	printf("OR = %d\n", z);

	z = x ^ y;
	printf("XOR = %d\n", z);

	z = x << 1;
	printf("Left Shift = %d\n", z);

	z = x >> 2;
	printf("Right Shift = %d\n", z);

	return 0;
}