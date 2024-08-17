#include <stdio.h>

void shell_sort(int v[], int n);

int main() {
  int v[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = 9;
  shell_sort(v, n);
  for (int i = 0; i < n; i++) {
    printf("%d ", v[i]);
  }
  printf("\n");
  return 0;
}

void shell_sort(int v[], int n) {
  int gap, i, j, temp;
  for (gap = n >> 1; gap > 0; gap >>= 1) {
    for (i = gap; i < n; i++) {
      for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
        temp = v[j];
        v[j] = v[j + gap];
        v[j + gap] = temp;
      }
    }
  }
}