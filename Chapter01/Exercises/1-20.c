#include <stdio.h>

#define TAB_STOP 8

int main() {
  char c;
  int column = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      int spaces = TAB_STOP - column % TAB_STOP;
      for (int i = 0; i < spaces; i++) {
        putchar(' ');
        column++;
      }
    } else {
      putchar(c);
      column++;
      if (c == '\n') {
        column = 0;
      }
    }
  }

  return 0;
}