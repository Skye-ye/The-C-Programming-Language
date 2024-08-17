#include <ctype.h>
#include <stdio.h>

#include "calc.h"

int getop(char s[]) {
  int i, c;
  static int lastc = ' ';

  while ((s[0] = c = lastc) == ' ' || c == '\t') {
    lastc = getch();
  }

  s[1] = '\0';

  i = 0;
  if (isalpha(c)) {
    while (isalpha(s[++i] = c = getch()));
    s[i] = '\0';
    lastc = c;
    return NAME;
  }

  if (!isdigit(c) && c != '.' && c != '-' && c != '+') {
    lastc = ' ';
    return c;
  }

  if (c == '-' || c == '+') {
    lastc = c = getch();
    if (!isdigit(c) && c != '.') {
      return s[0];
    }
    s[++i] = c;
  }

  if (isdigit(c)) {
    while (isdigit(s[++i] = c = getch()));
  }
  if (c == '.') {
    while (isdigit(s[++i] = c = getch()));
  }

  s[i] = '\0';
  lastc = c;
  return NUMBER;
}
