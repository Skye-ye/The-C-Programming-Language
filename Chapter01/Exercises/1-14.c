#include <stdio.h>

#define MAX_CHAR 256

int main() {
  int c;
  int char_freq[MAX_CHAR] = {0};

  printf(
      "Enter text (press Ctrl+D on Unix or Ctrl+Z on Windows to indicate "
      "EOF):\n");

  while ((c = getchar()) != EOF) {
    if (c >= 0 && c < MAX_CHAR) {
      char_freq[c]++;
    }
  }

  printf("\nHistogram of Character Frequencies:\n");
  for (int i = 0; i < MAX_CHAR; i++) {
    if (char_freq[i] > 0) {
      if (i == '\n') {
        printf("\\n: ");
      } else if (i == '\t') {
        printf("\\t: ");
      } else if (i == ' ') {
        printf("' ': ");
      } else {
        printf("%c: ", i);
      }
      for (int j = 0; j < char_freq[i]; j++) {
        putchar('#');
      }
      putchar('\n');
    }
  }

  return 0;
}
