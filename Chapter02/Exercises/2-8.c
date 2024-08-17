#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main() {
  unsigned x = 0xF994;
  int n = 4;

  printf("x: 0x%X\n", x);
  printf("n: %d\n", n);

  unsigned result = rightrot(x, n);
  printf("Result: 0x%X\n", result);

  return 0;
}

unsigned rightrot(unsigned x, int n) {
  int bit_width = 8 * sizeof(x);

  if (n == 0) return x;

  return (x >> n) | (x << (bit_width - n));
}