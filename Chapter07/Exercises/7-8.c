#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 80
#define LINES_PER_PAGE 50
#define MAX_FILES 10

void print_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file: %s\n", filename);
    return;
  }

  char line[MAX_LINE_LENGTH];
  int line_count = 0;
  int page_count = 1;

  printf("\n\n%s\n\n", filename);
  printf("Page %d\n\n", page_count);

  while (fgets(line, sizeof(line), file) != NULL) {
    printf("%s", line);
    line_count++;

    if (line_count == LINES_PER_PAGE) {
      printf("\n\n%s - Page %d\n", filename, page_count);

      printf("\f\n\n%s\n\n", filename);
      page_count++;
      printf("Page %d\n\n", page_count);

      line_count = 0;
    }
  }

  if (line_count > 0) {
    for (int i = line_count; i < LINES_PER_PAGE; i++) {
      printf("\n");
    }
    printf("\n\n%s - Page %d\n", filename, page_count);
  }

  printf("\f");
  fclose(file);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s file1 [file2 ...]\n", argv[0]);
    exit(1);
  }

  int num_files = argc - 1;
  if (num_files > MAX_FILES) {
    fprintf(stderr, "Too many files. Maximum is %d.\n", MAX_FILES);
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    print_file(argv[i]);
  }

  return 0;
}