#include <stdio.h>
#include <stdlib.h>

#define INITIAL_MAXLINE 100

int my_getline(char **buffer, int *buffer_size);
void strip_trailing_whitespace(char *line, int len);

int main() {
  int len;
  char *line = NULL;
  int line_size = INITIAL_MAXLINE;

  line = (char *)malloc(line_size * sizeof(char));
  if (line == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  while ((len = my_getline(&line, &line_size)) != -1) {
    strip_trailing_whitespace(line, len);
    if (line[0] != '\0') printf("%s\n", line);
  }

  free(line);

  return 0;
}

int my_getline(char **buffer, int *buffer_size) {
  int c, i = 0;

  while ((c = getchar()) != EOF && c != '\n') {
    if (i >= *buffer_size) {
      *buffer_size *= 2;
      *buffer = (char *)realloc(*buffer, *buffer_size * sizeof(char));
      if (*buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
      }
    }
    (*buffer)[i++] = c;
  }

  if (i == 0 && c == EOF) return -1;

  if (i >= *buffer_size) {
    *buffer_size *= 2;
    *buffer = (char *)realloc(*buffer, *buffer_size * sizeof(char));
    if (*buffer == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }
  }
  (*buffer)[i] = '\0';

  return i;
}

void strip_trailing_whitespace(char *line, int len) {
  int i = len;
  while (i >= 0 && (line[i - 1] == ' ' || line[i - 1] == '\t')) i--;
  line[i] = '\0';
}
