#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINES 10000
#define MAX_LENGTH 2000

void generate_random_string(char *str, int length) {
  char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";

  while (length-- > 0) {
    size_t index = (double)rand() / RAND_MAX * (sizeof(charset) - 1);
    *str++ = charset[index];
  }
  *str = '\0';
}

int main() {
  int n, len;
  char line[MAX_LENGTH + 1];

  srand(time(NULL));

  for (n = 0; n < MAX_LINES; n++) {
    len = rand() % MAX_LENGTH + 1;
    generate_random_string(line, len);
    printf("%s\n", line);
  }

  return 0;
}
