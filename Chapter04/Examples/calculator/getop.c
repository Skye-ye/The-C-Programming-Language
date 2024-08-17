#include <ctype.h>
#include <stdio.h>

#include "calc.h"

int getop(char s[]) {
  int i, c, next;

  while ((s[0] = c = getch()) == ' ' || c == '\t');

  s[1] = '\0';

  i = 0;
  if (isalpha(c)) {
    next = getch();
    if (!isalpha(next)) {
      ungetch(next);
      return VARIABLE;
    }
    s[++i] = c = next;
    while (isalpha(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF) {
      ungetch(c);
    }
    return NAME;
  }

  if (!isdigit(c) && c != '.' && c != '-' && c != '+') {
    return c;
  }

  if (c == '-' || c == '+') {
    next = getch();
    if (!isdigit(next) && next != '.') {
      ungetch(next);
      return c;
    }
    s[++i] = c = next;
  }

  if (isdigit(c)) {
    while (isdigit(s[++i] = c = getch()));
  }
  if (c == '.') {
    while (isdigit(s[++i] = c = getch()));
  }

  s[i] = '\0';
  if (c != EOF) {
    ungetch(c);
  }
  return NUMBER;
}
