#include <stdio.h>

#include "calc.h"

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

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
