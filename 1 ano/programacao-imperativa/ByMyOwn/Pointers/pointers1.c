#include <stdio.h>

int main() {
  int x = 4; // english: "integer named x is set to 4"
  
  int * pX = &x; // "integer pointer named pX is set to the address of x"
  
  int y = *pX; // "integer named y is set to the thing pointed to by pX"


  int z = 5; *ptr = &z; // variable and pointer in 1 line


  return 0;
}
