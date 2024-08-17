#include <ctype.h>
#include <stdio.h>

void expand(const char s1[], char s2[]);

int main() {
  char s1[] = "-a-z0-9-";
  char s2[100];
  expand(s1, s2);
  printf("%s\n", s2);
  return 0;
}

void expand(const char s1[], char s2[]) {
  int i = 0, j = 0;
  char c;

  while (s1[i] != '\0') {
    if (s1[i] == '-' && i > 0 && s1[i + 1] != '\0' && s1[i - 1] < s1[i + 1]) {
      for (c = s1[i - 1] + 1; c <= s1[i + 1]; c++) {
        s2[j++] = c;
      }
      i++;
    } else {
      s2[j++] = s1[i];
    }
    i++;
  }
  s2[j] = '\0';
}