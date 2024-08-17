#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100
#define NUMBER '0'
#define NAME '1'
#define VARIABLE '2'

int sp = 0;
int bufp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
double variables[26];
int variable_available[26];
int set_var = 0;

void push(double);
double pop(void);
double top(void);
void duplicate(void);
void swap(void);
void clear(void);

int getch(void);
void ungetch(int);
void ungets(char[]);
int getop(char[]);

void mathfunc(char[]);

int main() {
  int type;
  double op2;
  char s[MAXOP];
  int var = 0;

  while ((type = getop(s)) != EOF) {
    switch (type) {
      case NUMBER:
        push(atof(s));
        break;
      case NAME:
        mathfunc(s);
        break;
      case VARIABLE:
        var = s[0] - 'a';
        if (variable_available[var]) {
          push(variables[var]);
        }
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
          push(fmod(pop(), op2));
        } else {
          printf("error: zero divisor\n");
        }
        break;
      case '=':
        set_var = 1;
        op2 = pop();
        if (var >= 0 && var < 26) {
          variables[var] = op2;
          variable_available[var] = 1;
          printf("variable %c set to %.8g\n", var + 'a', op2);
        } else {
          printf("error: invalid variable name\n");
        }
        break;
      case '\n':
        if (set_var)
          set_var = 0;
        else
          printf("\t%.8g\n", pop());
        clear();
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

  i = 0;
  if (islower(c)) {
    next = getch();
    if (!islower(next)) {
      ungetch(next);
      return VARIABLE;
    }
    s[++i] = c = next;
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

void ungets(char s[]) {
  int len = strlen(s);

  while (len > 0) {
    ungetch(s[--len]);
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