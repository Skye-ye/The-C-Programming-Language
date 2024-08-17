#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXVAL 1000

int sp = 0;
int stack[MAXVAL];

void push(int f) {
  if (sp < MAXVAL) {
    stack[sp++] = f;
  } else {
    printf("error: stack full, can't push %d\n", f);
  }
}

int pop(void) {
  if (sp > 0) {
    return stack[--sp];
  } else {
    printf("error: stack empty\n");
    return 0;
  }
}

int main(int argc, char *argv[]) {
  int op2;

  while (--argc > 0) {
    char *s = *++argv;

    if (isdigit(s[0]) || (s[0] == '-' && isdigit(s[1]))) {
      push(atoi(s));
    } else {
      switch (s[0]) {
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
          if (op2 != 0) {
            push(pop() / op2);
          } else {
            printf("error: zero divisor\n");
          }
          break;
        default:
          printf("error: unknown command %s\n", s);
          break;
      }
    }
  }

  printf("\t%d\n", pop());
  return 0;
}
