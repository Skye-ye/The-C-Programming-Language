#include <_stdio.h>

int main() {
  int c;
  while ((c = getchar()) != EOF) {
    printf("getchar() != EOF: %d\n", (c != EOF));
  }

  printf("getchar() != EOF: %d\n", (getchar() != EOF));

  return 0;
}
