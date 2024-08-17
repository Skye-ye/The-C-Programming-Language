#include <stdio.h>
#include <stdlib.h>

#define INITIAL_MAXLINE 100
#define GOAL 80

int my_getline(char **buffer, int *buffer_size);

int main() {
  int len;
  char *line = NULL;
  int line_size = INITIAL_MAXLINE;

  line = (char *)malloc(line_size * sizeof(char));
  if (line == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  while ((len = my_getline(&line, &line_size)) > 0)
    if (len > GOAL) printf("%s", line);

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

  if (c == '\n') {
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
