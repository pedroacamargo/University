#include <stdio.h>

int main() {
  int a = 5, *pA = &a;
  int b = 10, *pB = &b;
   
  // a = 5
  // pA = address a

  printf("PointerA number -> %d\n", pA); // this will point to the memory address and give the number of the memory location
  printf("PointerB number -> %d\n", pB);
  printf("Pointer value -> %d\n", *pA);
  return 0;
}
