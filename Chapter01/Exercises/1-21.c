#include <stdio.h>

#define TAB_STOP 8

int main() {
  char c;
  int column = 0, space_count = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      space_count++;
    } else {
      while (space_count > 0) {
        int next_tab_stop = TAB_STOP - column % TAB_STOP;
        if (next_tab_stop <= space_count) {
          putchar('\t');
          column += next_tab_stop;
          space_count -= next_tab_stop;
        } else {
          while (space_count > 0) {
            putchar(' ');
            column++;
            space_count--;
          }
        }
      }

      putchar(c);
      column++;
      if (c == '\n') {
        column = 0;
      }
    }
  }

  return 0;
}