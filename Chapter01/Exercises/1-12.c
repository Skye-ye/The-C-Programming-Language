#include <stdio.h>
#define IN 1
#define OUT 0

int main() {
  char c;
  int state = IN;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') 
      state = OUT;
    else {
      if (state == OUT) {
        state = IN;
        printf("\n");
      }
      putchar(c);
    }
  }
  printf("\n");

  return 0;
}
