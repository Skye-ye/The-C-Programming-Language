#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define MAXOCCURENCES 100
#define BUFSIZE 10
#define NKEYS (sizeof(noisy_words) / sizeof(char *))

struct tnode {
  char *word;
  int count;
  int lines[MAXOCCURENCES];
  struct tnode *left;
  struct tnode *right;
};

struct tnode *talloc(void);
char *str_dup(char *);
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
void freetree(struct tnode *);
int binsearch(char *, char *[], int);
int getword(char *, int);

char *noisy_words[] = {"a",    "an",  "and",   "are",  "as",    "at",    "be",
                       "but",  "by",  "for",   "if",   "in",    "into",  "is",
                       "it",   "no",  "not",   "of",   "on",    "or",    "such",
                       "that", "the", "their", "then", "there", "these", "they",
                       "this", "to",  "was",   "will", "with"};

int buf[BUFSIZE];
int bufp = 0;

int main() {
  struct tnode *root;
  char word[MAXWORD];
  int line_number;

  root = NULL;
  while ((line_number = getword(word, MAXWORD)) != -1) {
    if (isalpha(word[0]) && !binsearch(word, noisy_words, NKEYS)) {
      root = addtree(root, word, line_number);
    }
  }

  treeprint(root);
  freetree(root);
  return 0;
}

struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

char *str_dup(char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL) {
    strcpy(p, s);
  }
  return p;
}

struct tnode *addtree(struct tnode *p, char *w, int line_number) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = str_dup(w);
    p->count = 1;
    p->lines[0] = line_number;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->lines[p->count++] = line_number;
  } else if (cond < 0) {
    p->left = addtree(p->left, w, line_number);
  } else {
    p->right = addtree(p->right, w, line_number);
  }

  return p;
}

void treeprint(struct tnode *p) {
  if (p != NULL) {
    treeprint(p->left);
    printf("%s:", p->word);
    for (int i = 0; i < p->count; i++) {
      printf(" %d", p->lines[i]);
    }
    printf("\n");
    treeprint(p->right);
  }
}

void freetree(struct tnode *p) {
  if (p != NULL) {
    freetree(p->left);
    freetree(p->right);
    free(p->word);
    free(p);
  }
}

int binsearch(char *word, char *list[], int n) {
  int cond;
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, list[mid])) < 0) {
      high = mid - 1;
    } else if (cond > 0) {
      low = mid + 1;
    } else {
      return 1;
    }
  }

  return 0;
}

int getword(char *word, int lim) {
  static int line = 1;
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch())) {
    if (c == '\n') {
      line++;
    }
  }

  if (c == EOF) {
    return -1;
  }

  *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return line;
  }
  for (; --lim > 0; w++)
    if (!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }
  *w = '\0';
  return line;
}

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}
