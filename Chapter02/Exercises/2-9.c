#include <stdio.h>

int bitcount(unsigned x);

int main() {
  unsigned x = 0xF994;
  printf("x: 0x%X\n", x);
  printf("Result: %d\n", bitcount(x));
  return 0;
}

int bitcount(unsigned x) {
  int count = 0;
  while (x) {
    x &= (x - 1);
    count++;
  }
  return count;
}