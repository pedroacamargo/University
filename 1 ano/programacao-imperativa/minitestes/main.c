#include <stdio.h>

int main() {
  int i;
  int acc = 0;
  for(i = 4; i < 29; i+=4) {
     acc++;
  }

    printf("%d",acc);

  return 0;
}