#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main() {
  unsigned x = 0xF994;
  int p = 7;
  int n = 4;

  printf("x: 0x%X\n", x);
  printf("p: %d\n", p);
  printf("n: %d\n", n);

  unsigned result = invert(x, p, n);
  printf("Result: 0x%X\n", result);

  return 0;
}

unsigned invert(unsigned x, int p, int n) {
  unsigned mask = ~(~0 << n) << (p - n + 1);
  return x ^ mask;
}