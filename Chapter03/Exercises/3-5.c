#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[]);
void itob(int n, char s[], int b);

int main() {
  char buffer[50];
  itob(-255, buffer, 16);
  printf("Hexadecimal: %s\n", buffer);

  itob(-255, buffer, 2);
  printf("Binary: %s\n", buffer);

  itob(-255, buffer, 10);
  printf("Decimal: %s\n", buffer);

  return 0;
}

void itob(int n, char s[], int b) {
  int i = 0;
  int sign = n;
  int remainder;

  if (b < 2 || b > 36) {
    printf("Base must be between 2 and 36\n");
    return;
  }

  if (sign < 0 && b == 10) {
    n = -n;
  }

  do {
    remainder = abs(n % b);
    s[i++] = (remainder > 9) ? 'A' + remainder - 10 : '0' + remainder;
  } while (n /= b);

  if (sign < 0 && b == 10) {
    s[i++] = '-';
  }

  s[i] = '\0';
  reverse(s);
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