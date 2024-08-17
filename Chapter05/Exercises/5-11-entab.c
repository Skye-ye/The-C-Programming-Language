#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAP_STOP 8

int is_tab_stop(int column, int argc, char *argv[]) {
  if (argc == 1) {
    return column % DEFAULT_TAP_STOP == 0;
  } else {
    for (int i = 1; i < argc; i++) {
      if (column % atoi(argv[i]) == 0) {
        return 1;
      }
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  char c;
  int column = 0, space_count = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ')
      space_count++;
    else {
      while (space_count > 0) {
        int next_tab_stop = 1;
        while (!is_tab_stop(column + next_tab_stop, argc, argv)) {
          next_tab_stop++;
        }

        if (space_count >= next_tab_stop) {
          putchar('\t');
          space_count -= next_tab_stop;
          column += next_tab_stop;
        } else {
          while (space_count > 0) {
            putchar(' ');
            space_count--;
            column++;
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