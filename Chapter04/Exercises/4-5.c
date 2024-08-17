#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define NUMBER '0'
#define NAME 'n'

int sp = 0;
int bufp = 0;
double val[MAXVAL];
char buf[BUFSIZE];

void push(double);
double pop(void);
double top(void);
void duplicate(void);
void swap(void);
void clear(void);

int getch(void);
void ungetch(int);
int getop(char[]);

void mathfunc(char[]);

int main() {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
      case NUMBER:
        push(atof(s));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
      case '/':
        op2 = pop();
        if (op2 != 0.0) {
          push(pop() / op2);
        } else {
          printf("error: zero divisor\n");
        }
        break;
      case '%':
        op2 = pop();
        if (op2 != 0.0) {
          push((int)pop() % (int)op2);
        } else {
          printf("error: zero divisor\n");
        }
        break;
      case NAME:
        mathfunc(s);
        break;
      case '\n':
        printf("\t%.8g\n", pop());
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }
}

void push(double f) {
  if (sp < MAXVAL) {
    val[sp++] = f;
  } else {
    printf("error: stack full, can't push %g\n", f);
  }
}

double pop(void) {
  if (sp > 0) {
    return val[--sp];
  } else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

double top(void) {
  if (sp > 0) {
    return val[sp - 1];
  } else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

void duplicate(void) {
  double temp = top();
  push(temp);
}

void swap(void) {
  double temp1 = pop();
  double temp2 = pop();
  push(temp1);
  push(temp2);
}

void clear(void) { sp = 0; }

int getop(char s[]) {
  int i, c, next;

  while ((s[0] = c = getch()) == ' ' || c == '\t');

  s[1] = '\0';
  if (islower(c)) {
    i = 0;
    while (islower(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF) {
      ungetch(c);
    }
    return NAME;
  }

  if (!isdigit(c) && c != '.' && c != '-' && c != '+') {
    return c;
  }

  i = 0;
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

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}

void mathfunc(char s[]) {
  double op2;

  if (strcmp(s, "sin") == 0) {
    push(sin(pop()));
  } else if (strcmp(s, "exp") == 0) {
    push(exp(pop()));
  } else if (strcmp(s, "pow") == 0) {
    op2 = pop();
    push(pow(pop(), op2));
  } else {
    printf("error: %s not supported\n", s);
  }
}