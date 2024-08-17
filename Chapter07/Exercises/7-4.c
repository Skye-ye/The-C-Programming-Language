#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minscanf(char *fmt, ...);

int main() {
  int n;
  double x;
  char s[100];
  unsigned u;
  char c;
  void *ptr;

  printf("Enter an integer: ");
  minscanf("%d", &n);
  printf("You entered: %d\n", n);

  printf("Enter a float: ");
  minscanf("%f", &x);
  printf("You entered: %f\n", x);

  printf("Enter a string: ");
  minscanf("%s", s);
  printf("You entered: %s\n", s);

  printf("Enter an unsigned integer: ");
  minscanf("%u", &u);
  printf("You entered: %u\n", u);

  printf("Enter a character: ");
  minscanf("%c", &c);
  printf("You entered: %c\n", c);

  printf("Enter a hexadecimal number: ");
  minscanf("%x", &u);
  printf("You entered: %x\n", u);

  return 0;
}

int minscanf(char *fmt, ...) {
  va_list ap;
  const char *p;
  char *sval;
  int *ival;
  unsigned *uval;
  double *dval;
  void **pval;
  int count = 0;
  int read;

  va_start(ap, fmt);
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      if (*p == ' ' || *p == '\t' || *p == '\n') {
        while (*p == ' ' || *p == '\t' || *p == '\n') {
          p++;
        }
        scanf("%*[ \t\n]");
        p--;
      } else {
        if (getchar() != *p) {
          va_end(ap);
          return count;
        }
      }
      continue;
    }

    switch (*++p) {
      case 'd':
      case 'i':
        ival = va_arg(ap, int *);
        read = scanf("%d", ival);
        break;
      case 'u':
        uval = va_arg(ap, unsigned *);
        read = scanf("%u", uval);
        break;
      case 'f':
        dval = va_arg(ap, double *);
        read = scanf("%lf", dval);
        break;
      case 's':
        sval = va_arg(ap, char *);
        read = scanf("%s", sval);
        break;
      case 'c':
        sval = va_arg(ap, char *);
        read = scanf(" %c", sval);
        break;
      case 'x':
      case 'X':
        uval = va_arg(ap, unsigned *);
        read = scanf("%x", uval);
        break;
      case 'p':
        pval = va_arg(ap, void **);
        read = scanf("%p", pval);
        break;
      default:
        va_end(ap);
        return count;
    }

    if (read == 1) {
      count++;
    } else {
      va_end(ap);
      return count;
    }
  }

  va_end(ap);
  return count;
}