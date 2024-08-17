#include <limits.h>
#include <stdio.h>

void itoa_helper(int n, char s[], int *index) {
  if (n / 10) {
    itoa_helper(n / 10, s, index);
  }
  s[(*index)++] = (n % 10) + '0';
}

void itoa(int n, char s[]) {
  int index = 0;
  if (n < 0) {
    s[index++] = '-';
    if (n == INT_MIN) {
      s[index++] = '2';
      n = -(n % 1000000000);
    } else {
      n = -n;
    }
  }
  itoa_helper(n, s, &index);
  s[index] = '\0';
}

int main() {
  char s[100];
  itoa(123, s);
  printf("%s\n", s);
  itoa(-123, s);
  printf("%s\n", s);
  itoa(INT_MIN, s);
  printf("%s\n", s);
  return 0;
}