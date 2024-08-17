#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void minprintf(char *fmt, ...);

int main() {
  int n = 5;
  double x = 3.14159265;
  char s[] = "hello, world";
  unsigned u = 42;
  char c = 'A';
  void *ptr = &n;

  minprintf("Integer: %d\n", n);
  minprintf("Padded integer: %5d\n", n);
  minprintf("Left-justified padded integer: %-5d\n", n);
  minprintf("Float: %f\n", x);
  minprintf("Precise float: %.2f\n", x);
  minprintf("String: %s\n", s);
  minprintf("Truncated string: %.5s\n", s);
  minprintf("Unsigned: %u\n", u);
  minprintf("Hexadecimal: %x %X\n", u, u);
  minprintf("Character: %c\n", c);
  minprintf("Pointer: %p\n", ptr);
  printf("Pointer: %p\n", ptr);

  return 0;
}

void minprintf(char *fmt, ...) {
  va_list ap;
  char *p, *sval;
  int ival;
  unsigned uval;
  double dval;
  va_start(ap, fmt);

  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }

    int left_justify = 0;
    if (*++p == '-') {
      left_justify = 1;
      p++;
    }

    int width = 0;
    while (*p >= '0' && *p <= '9') {
      width = width * 10 + (*p - '0');
      p++;
    }

    int precision = -1;
    if (*p == '.') {
      precision = 0;
      p++;
      while (*p >= '0' && *p <= '9') {
        precision = precision * 10 + (*p - '0');
        p++;
      }
    }

    char buf[1000];
    int len;

    switch (*p) {
      case 'd':
      case 'i':
        ival = va_arg(ap, int);
        len = snprintf(buf, sizeof(buf), "%d", ival);
        break;
      case 'u':
        uval = va_arg(ap, unsigned);
        len = snprintf(buf, sizeof(buf), "%u", uval);
        break;
      case 'f':
        dval = va_arg(ap, double);
        if (precision >= 0) {
          len = snprintf(buf, sizeof(buf), "%.*f", precision, dval);
        } else {
          len = snprintf(buf, sizeof(buf), "%f", dval);
        }
        break;
      case 's':
        sval = va_arg(ap, char *);
        len = strlen(sval);
        if (precision >= 0 && len > precision) {
          len = precision;
        }
        break;
      case 'c':
        buf[0] = (char)va_arg(ap, int);
        len = 1;
        break;
      case 'x':
      case 'X':
        uval = va_arg(ap, unsigned);
        len = snprintf(buf, sizeof(buf), *p == 'x' ? "%x" : "%X", uval);
        break;
      case 'p':
        len = snprintf(buf, sizeof(buf), "%p", va_arg(ap, void *));
        break;
      default:
        putchar(*p);
        continue;
    }

    if (!left_justify) {
      for (int i = len; i < width; i++) {
        putchar(' ');
      }
    }

    if (*p == 's') {
      printf("%.*s", len, sval);
    } else {
      printf("%.*s", len, buf);
    }

    if (left_justify) {
      for (int i = len; i < width; i++) {
        putchar(' ');
      }
    }
  }

  va_end(ap);
}