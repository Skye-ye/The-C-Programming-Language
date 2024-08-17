#include <stdio.h>

int htoi(const char s[]);

int main() {
  char *hex_string1 = "1a3f";
  char *hex_string2 = "0x1A3F";
  char *hex_string3 = "0XABC";
  char *hex_string4 = "abc";

  printf("%s in decimal is %d\n", hex_string1, htoi(hex_string1));
  printf("%s in decimal is %d\n", hex_string2, htoi(hex_string2));
  printf("%s in decimal is %d\n", hex_string3, htoi(hex_string3));
  printf("%s in decimal is %d\n", hex_string4, htoi(hex_string4));

  return 0;
}

int htoi(const char s[]) {
  int i = 0;
  int result = 0;
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    i = 2;
  }
  while (s[i] != '\0') {
    if (s[i] >= '0' && s[i] <= '9') {
      result = result * 16 + s[i] - '0';
    } else if (s[i] >= 'a' && s[i] <= 'f') {
      result = result * 16 + s[i] - 'a' + 10;
    } else if (s[i] >= 'A' && s[i] <= 'F') {
      result = result * 16 + s[i] - 'A' + 10;
    } else {
      return 0;
    }
    i++;
  }
  return result;
}