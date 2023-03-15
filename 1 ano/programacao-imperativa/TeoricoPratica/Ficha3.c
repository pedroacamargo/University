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
void swap(int *a, int *b) {
  int tmp = (*b);
  (*b) = (*a);
  (*a) = tmp;
}

// 3)
void swap2(int v[], int i, int j) {
  int *x, *y, tmp;
  x = v + i;
  y = v + j;

  tmp = *y;
  *y = *x;
  *x = tmp;
}

// 4)
int soma(int v[], int N) {
  int soma = 0;

  for (int i = 0; i < N ; i++) {
    soma += v[i];
  }

  return soma;
} 

void inverteArray(int v[], int N) {
  int stop = N/2;



  for (int i = 0; i <= stop; i++) {
    swap2(v, i, N - i -1);
  }
}

int main() {
	// swap();
	// int x = 3, y = 5;

	// swap(&x, &y);

  
  //swap2() 
  // int x = 0, y = 3;
  // int array[] = {0,1,2,3,4,5,6,7};
  // swap2(array,x,y);

  // printf("x -> %d\ny -> %d",array[0],array[3]);
  // for (int i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
    // printf("%d , ", array[i]);
  // }
  // int x = 5;
  // int array[] = {1,2,3,4,5,6,7,8};
  // int res = soma(array, x);
  
  int array[] = {1,2,3,4,5,6,7};
  inverteArray(array, 6);
  printf("%d",array[0]);
  for (int i = 0; i < 7; i++) {
    printf("%d", array[i]);
  }

	return 0;
}

