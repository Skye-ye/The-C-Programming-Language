#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void itoa(int n, char s[]);

int main() {
  char buffer[20];
  itoa(-2147483648, buffer);
  printf("%s\n", buffer);
  return 0;
}

void reverse(char s[]) {
  int i, j;
  char c;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoa(int n, char s[]) {
  int i = 0;
  int sign = n;

  do {
    s[i++] = '0' - n % 10;
  } while ((n /= 10) != 0);

  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';

  reverse(s);
}