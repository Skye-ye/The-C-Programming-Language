#ifndef CALC_H
#define CALC_H

#define NUMBER '0'
#define NAME '1'
#define VARIABLE '2'

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

#endif  // CALC_H
