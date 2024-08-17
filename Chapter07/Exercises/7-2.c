#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 60
#define OCTAL_PRINT 0

void print_char(int c) {
  if (isprint(c)) {
    putchar(c);
  } else {
    if (OCTAL_PRINT) {
      printf("\\%03o", c);
    } else {
      printf("\\x%02X", c);
    }
  }
}

int main() {
  int c;
  int column = 0;

  while ((c = getchar()) != EOF) {
    int char_width = isprint(c) ? 1 : (OCTAL_PRINT ? 4 : 4);

    if (column + char_width > MAX_LINE_LENGTH && c != '\n') {
      putchar('\n');
      column = 0;
    }

    print_char(c);

    if (c == '\n') {
      column = 0;
    } else {
      column += char_width;
    }
  }

  if (column > 0) {
    putchar('\n');
  }

  return 0;
}