#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_MAXLINE 100

int my_getline(char **buffer, int *buffer_size);
void copy(char **dest, char *src, int *dest_size);

int main() {
  int len;
  int max = 0;
  char *line = NULL;
  char *longest = NULL;
  int line_size = INITIAL_MAXLINE;
  int longest_size = INITIAL_MAXLINE;

  line = (char *)malloc(line_size * sizeof(char));
  if (line == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  longest = (char *)malloc(longest_size * sizeof(char));
  if (longest == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  while ((len = my_getline(&line, &line_size)) > 0) {
    if (len > max) {
      max = len;
      copy(&longest, line, &longest_size);
    }
  }

  if (max > 0) {
    printf("Longest line length: %d\n", max);
    printf("%s", longest);
  }

  free(line);
  free(longest);

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

void copy(char **dest, char *src, int *dest_size) {
  int len = 0;
  while (src[len] != '\0') {
    len++;
  }

  if (len >= *dest_size) {
    *dest_size = len + 1;
    *dest = (char *)realloc(*dest, *dest_size * sizeof(char));
    if (*dest == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i <= len; i++) {
    (*dest)[i] = src[i];
  }
}