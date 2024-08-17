#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main() {
  unsigned x = 0xF994;
  unsigned y = 0x0F3;
  int p = 7;
  int n = 4;

  printf("x: 0x%X\n", x);
  printf("y: 0x%X\n", y);
  printf("p: %d\n", p);
  printf("n: %d\n", n);

  unsigned result = setbits(x, p, n, y);
  printf("Result: 0x%X\n", result);

  return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
  unsigned mask = ~(~0 << n) << (p - n + 1);
  x &= ~mask;
  y = (y & ~(~0 << n)) << (p - n + 1);
  return x | y;
}