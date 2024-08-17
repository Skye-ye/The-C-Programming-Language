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

int my_getline(char s[], int lim);
int getop(char[], const char[], int*);

void mathfunc(char[]);

int main() {
  int type;
  double op2;
  char s[MAXOP];
  int var = 0;
  char t[MAXOP];
  int p;

  while (my_getline(t, MAXOP) > 0) {
    p = 0;
    while ((type = getop(s, t, &p)) != -1) {
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

int my_getline(char s[], int lim) {
  int c, i;

  i = 0;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
    s[i++] = c;
  }
  if (c == '\n') {
    s[i++] = c;
  }
  s[i] = '\0';
  return i;
}

int getop(char s[], const char t[], int* p) {
  int i = 0, c;
  if (t[*p] == '\0') {
    return -1;
  }

  while ((s[0] = c = t[(*p)++]) == ' ' || c == '\t');
  s[1] = '\0';

  if (islower(c)) {
    if (!islower(t[*p])) {
      return VARIABLE;
    }
    s[++i] = c = t[(*p)++];
    while (islower(s[++i] = c = t[(*p)++]));
    s[i] = '\0';
    (*p)--;
    return NAME;
  }

  if (!isdigit(c) && c != '.' && c != '-' && c != '+') {
    return c;
  }

  if (c == '-' || c == '+') {
    if (!isdigit(c = t[(*p)++])) {
      (*p)--;
      return c;
    }
    s[++i] = c;
  }

  if (isdigit(c)) {
    while (isdigit(s[++i] = c = t[(*p)++]));
  }

  if (c == '.') {
    while (isdigit(s[++i] = c = t[(*p)++]));
  }

  s[i] = '\0';
  (*p)--;
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