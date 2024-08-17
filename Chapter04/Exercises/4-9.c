#include <stdio.h>

#define BUFFER_EMPTY -2

static int buf = BUFFER_EMPTY;

int getch(void) {
  int temp;
  if (buf != BUFFER_EMPTY) {
    temp = buf;
    buf = BUFFER_EMPTY;
    return temp;
  } else {
    return getchar();
  }
}

void ungetch(int c) {
  if (buf != BUFFER_EMPTY) {
    printf("ungetch error: buffer full\n");
  } else {
    buf = c;
  }
}
