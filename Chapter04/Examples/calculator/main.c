#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calc.h"

#define MAXOP 100
double variables[26];
int variable_available[26];

int main(void) {
  int type;
  double op2;
  char s[MAXOP];
  int var = 0;
  int set_var = 0;

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
