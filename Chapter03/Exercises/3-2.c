#include <stdio.h>

void escape(char s[], const char t[]);
void unescape(char s[], const char t[]);

int main() {
  char t[] = "Hello\tworld!\nThis is a test.";
  char s[100];
  char back[100];

  escape(s, t);
  printf("Escaped: %s\n", s);

  unescape(back, s);
  printf("Unescaped: %s\n", back);

  return 0;
}

void escape(char s[], const char t[]) {
  int i, j;
  for (i = j = 0; t[i] != '\0'; i++) {
    switch (t[i]) {
      case '\t':
        s[j++] = '\\';
        s[j++] = 't';
        break;
      case '\n':
        s[j++] = '\\';
        s[j++] = 'n';
        break;
      default:
        s[j++] = t[i];
        break;
    }
  }
  s[j] = '\0';
}

void unescape(char s[], const char t[]) {
  int i, j;
  for (i = j = 0; t[i] != '\0'; i++) {
    if (t[i] == '\\') {
      switch (t[++i]) {
        case 't':
          s[j++] = '\t';
          break;
        case 'n':
          s[j++] = '\n';
          break;
        default:
          s[j++] = '\\';
          s[j++] = t[i];
          break;
      }
    } else {
      s[j++] = t[i];
    }
  }
  s[j] = '\0';
}