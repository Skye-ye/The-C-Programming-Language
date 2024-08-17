#include <stdio.h>
#include <stdlib.h>

#define INITIAL_MAXLINE 100

int my_getline(char **buffer, int *buffer_size);
void reverse(char **dest, char *src, int len, int *dest_size);

int main() {
  int len;
  char *line = NULL;
  char *reversed_line = NULL;
  int line_size = INITIAL_MAXLINE;
  int reversed_line_size = INITIAL_MAXLINE;

  line = (char *)malloc(line_size * sizeof(char));
  if (line == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  reversed_line = (char *)malloc(reversed_line_size * sizeof(char));
  if (reversed_line == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  while ((len = my_getline(&line, &line_size)) != -1) {
    reverse(&reversed_line, line, len, &reversed_line_size);
    printf("%s\n", reversed_line);
  }

  free(line);
  free(reversed_line);

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

void reverse(char **dest, char *src, int len, int *dest_size) {
  if (len >= *dest_size) {
    *dest_size *= 2;
    *dest = (char *)realloc(*dest, *dest_size * sizeof(char));
    if (*dest == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }
  }

  int i;
  for (i = 0; i < len; i++) {
    (*dest)[i] = src[len - i - 1];
  }
  (*dest)[i] = '\0';
}
