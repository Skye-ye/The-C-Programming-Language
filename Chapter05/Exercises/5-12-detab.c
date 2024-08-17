#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_STOP 8
#define DEFAULT_START_COLUMN 0

int is_tab_stop(int column, int start, int interval) {
  return (column >= start) && ((column - start) % interval == 0);
}

int main(int argc, char *argv[]) {
  char c;
  int column = 0;
  int start = DEFAULT_START_COLUMN;
  int interval = DEFAULT_TAB_STOP;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      start = atoi(argv[i] + 1);
    } else if (argv[i][0] == '+') {
      interval = atoi(argv[i] + 1);
    }
  }

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      do {
        putchar(' ');
        column++;
      } while (!is_tab_stop(column, start, interval));
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
