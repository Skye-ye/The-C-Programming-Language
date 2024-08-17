#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int main(int argc, char *argv[]) {
  char line[MAXLINE];
  int found = 0;

  if (argc != 2) {
    printf("Usage: find pattern\n");
  } else {
    while (fgets(line, MAXLINE, stdin) != NULL) {
      if (strstr(line, argv[1]) != NULL) {
        printf("%s", line);
        found++;
      }
    }
  }
  return 0;
}