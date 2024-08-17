#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int c);
int getfloat(double *pn);

int main() {
  int n = 0;
  double array[100];
  while (n < 100) {
    int result = getfloat(&array[n]);
    if (result == -1) {
      break;
    }
    if (result == 0) {
      continue;
    }
    n++;
  }
  for (int i = 0; i < n; i++) {
    printf("%f ", array[i]);
  }
  printf("\n");
  return 0;
}

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}

int getfloat(double *pn) {
  double power = 1.0;
  int c, sign, exp_sign, exp;

  while (isspace(c = getch()));

  if (!isdigit(c) && c != '.' && c != '+' && c != '-' && c != EOF) {
    ungetch(c);
    return 0;
  }

  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    c = getch();
    if (!isdigit(c) && c != '.') {
      ungetch(c);
      return 0;
    }
  }

  for (*pn = 0.0; isdigit(c); c = getch()) {
    *pn = 10.0 * *pn + (c - '0');
  }

  if (c == '.') {
    c = getch();
    for (power = 1.0; isdigit(c); c = getch()) {
      *pn = 10.0 * *pn + (c - '0');
      power *= 10.0;
    }
  }

  if (c == 'e' || c == 'E') {
    c = getch();
    exp_sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
      c = getch();
    }
    for (exp = 0; isdigit(c); c = getch()) {
      exp = 10 * exp + (c - '0');
    }
    if (exp_sign == 1) {
      while (exp-- > 0) {
        *pn *= 10;
      }
    } else {
      while (exp-- > 0) {
        *pn /= 10;
      }
    }
  }

  *pn = sign * (*pn / power);

  if (c != EOF) {
    ungetch(c);
  }

  return c == EOF ? -1 : 1;
}