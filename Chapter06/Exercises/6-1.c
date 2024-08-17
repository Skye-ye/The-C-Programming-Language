#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define NKEYS (sizeof keytab / sizeof keytab[0])

#define MAXWORD 100
#define BUFSIZE 1000

struct key {
  char *word;
  int count;
} keytab[] = {{"auto", 0},  {"break", 0},    {"case", 0},    {"char", 0},
              {"const", 0}, {"continue", 0}, {"default", 0}, {"unsigned", 0},
              {"void", 0},  {"volatile", 0}};

int buf[BUFSIZE];
int bufp = 0;

int getword(char *, int);
int binsearch(char *, struct key *, int);

int main() {
  int n;
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]) || word[0] == '_')
      if ((n = binsearch(word, keytab, NKEYS)) >= 0) keytab[n].count++;
  for (n = 0; n < NKEYS; n++)
    if (keytab[n].count > 0)
      printf("%4d %s\n", keytab[n].count, keytab[n].word);
}

int getword(char *word, int lim) {
  int c, d, getch(void);
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch()));

  if (c == EOF) return c;

  *w++ = c;

  if (isalpha(c) || c == '_') {
    for (; --lim > 0; w++)
      if (!isalnum(*w = getch()) && *w != '_') {
        if (*w != EOF) {
          ungetch(*w);
          break;
        }
      }
  } else if (c == '/') {
    if ((d = getch()) == '*') {
      while ((c = getch()) != EOF) {
        if (c == '*') {
          if ((c = getch()) == '/') {
            break;
          } else {
            ungetch(c);
          }
        }
      }
    } else {
      ungetch(d);
    }
  } else if (c == '#') {
    while ((c = getch()) != '\n' && c != EOF);
  }

  *w = '\0';
  return word[0];
}

int binsearch(char *word, struct key tab[], int n) {
  int cond;
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, tab[mid].word)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}