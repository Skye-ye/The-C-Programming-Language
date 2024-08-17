#include <stdio.h>

#define MAX_WORD_LENGTH 20

int main() {
  int c, i, j, word_length, max_count;
  int word_lengths[MAX_WORD_LENGTH + 1] = {0};

  word_length = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      if (word_length > 0) {
        if (word_length <= MAX_WORD_LENGTH) {
          word_lengths[word_length]++;
        } else {
          word_lengths[MAX_WORD_LENGTH]++;
        }
        word_length = 0;
      }
    } else {
      word_length++;
    }
  }

  max_count = 0;
  for (i = 1; i <= MAX_WORD_LENGTH; i++) {
    if (word_lengths[i] > max_count) {
      max_count = word_lengths[i];
    }
  }

  printf("\nVertical Histogram of Word Lengths\n");
  for (i = max_count; i > 0; i--) {
    for (j = 1; j <= MAX_WORD_LENGTH; j++) {
      if (word_lengths[j] >= i) {
        printf(" # ");
      } else {
        printf("   ");
      }
    }
    putchar('\n');
  }

  for (i = 1; i <= MAX_WORD_LENGTH; i++) {
    printf("---");
  }
  putchar('\n');
  for (i = 1; i <= MAX_WORD_LENGTH; i++) {
    printf("%2d ", i);
  }
  putchar('\n');

  return 0;
}
