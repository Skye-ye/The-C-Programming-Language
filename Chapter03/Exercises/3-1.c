#include <stdio.h>

int binsearch(int x, int v[], int n);

int main() {
  int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int n = 9;
  int x = 5;
  int p = binsearch(x, v, n);
  if (p == -1) {
    printf("Not found\n");
  } else {
    printf("Found at %d\n", p);
  }
  return 0;
}

int binsearch(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low < high) {
    mid = low + high >> 1;
    if (x <= v[mid]) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }

  return x == v[low] ? low : -1;
}
