#include <stdio.h>

int main() {
  char c;
  int last_char_was_blank = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      if (!last_char_was_blank) {
        putchar(c);
        last_char_was_blank = 1;
      }
    } else {
      putchar(c);
      last_char_was_blank = 0;
    }
  }

  return 0;
}
