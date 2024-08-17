#include <stdio.h>
#include <string.h>

void reverse_helper(char s[], int st, int ed) {
  if (st >= ed) {
    return;
  }
  char tmp = s[st];
  s[st] = s[ed];
  s[ed] = tmp;
  reverse_helper(s, st + 1, ed - 1);
}

void reverse(char s[]) {
  int len = strlen(s);
  reverse_helper(s, 0, len - 1);
}

int main() {
  char s[] = "hello";
  reverse(s);
  printf("%s\n", s);
  return 0;
}