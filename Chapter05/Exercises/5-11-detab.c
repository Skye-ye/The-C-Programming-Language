#include <stdio.h>

#define DEFAULT_TAB_STOP 8

int main(int argc, char *argv[]) {
  char c;
  int column = 0;
  int tab_stop;

  if (argc > 2) {
    printf("Usage: detab [tab_stop]\n");
    return 1;
  }

  if (argc == 1) {
    tab_stop = DEFAULT_TAB_STOP;
  } else {
    if (!isdigit(argv[1][0]) || (tab_stop = atoi(argv[1])) <= 0) {
      printf("Invalid tab stop: %s\n", argv[1]);
      return 1;
    }
  }

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      int spaces = tab_stop - column % tab_stop;
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