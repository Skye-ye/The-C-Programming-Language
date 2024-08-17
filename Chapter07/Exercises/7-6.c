#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int main(int argc, char *argv[]) {
  FILE *fp1, *fp2;
  void filediff(FILE *, FILE *);

  if (argc != 3) {
    fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
    exit(1);
  }

  if ((fp1 = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "%s: can't open %s\n", argv[0], argv[1]);
    exit(2);
  }

  if ((fp2 = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "%s: can't open %s\n", argv[0], argv[2]);
    exit(2);
  }

  char s1[MAX], s2[MAX];
  while (fgets(s1, MAX, fp1) != NULL && fgets(s2, MAX, fp2) != NULL) {
    if (strcmp(s1, s2) != 0) {
      printf("Difference found:\n");
      printf("%s: %s", argv[1], s1);
      printf("%s: %s", argv[2], s2);
      break;
    }
  }
  fclose(fp1);
  fclose(fp2);
  return 0;
}