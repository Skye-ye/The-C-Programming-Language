#include <stdio.h>
#define MAXLINE 1000
int max;
char line[MAXLINE];
char longest[MAXLINE];
int my_getline(void);
void copy(void);

int main() {
  int len;
  max = 0;
  while ((len = my_getline()) > 0)
    if (len > max) {
      max = len;
      copy();
    }
  if (max > 0) /* there was a line */
    printf("%s", longest);
  return 0;
}

int my_getline(void) {
  int c, i;
  for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;
  if (c == '\n') {
    line[i] = c;
    ++i;
  }
  line[i] = '\0';
  return i;
}

void copy(void) {
  int i;
  i = 0;
  while ((longest[i] = line[i]) != '\0') ++i;
}