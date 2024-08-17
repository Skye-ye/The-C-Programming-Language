#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE (MAXLINES * MAXLEN + 10)

char *lineptr[MAXLINES];
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n);
void afree(char *p);
int get_line(char s[], int lim);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void quick_sort(void *lineptr[], int left, int right,
                int (*comp)(const void *, const void *), int reverse);

int numcmp(const char *, const char *);
int foldcmp(const char *, const char *);

int main(int argc, char *argv[]) {
  int nlines;
  int numeric = 0, reverse = 0, fold = 0;

  while (--argc > 0 && (*++argv)[0] == '-') {
    char *arg = *argv;
    while (*++arg) {
      switch (*arg) {
        case 'n':
          numeric = 1;
          break;
        case 'r':
          reverse = 1;
          break;
        case 'f':
          fold = 1;
          break;
        default:
          printf("Unknown option: %c\n", *arg);
          return 1;
      }
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    quick_sort((void **)lineptr, 0, nlines - 1,
               (int (*)(const void *, const void *))(
                   numeric ? numcmp : (fold ? foldcmp : strcmp)),
               reverse);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else {
    return 0;
  }
}

void afree(char *p) {
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
    allocp = p;
  }
}

int get_line(char s[], int lim) {
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

int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = get_line(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || (p = alloc(len)) == NULL) {
      return -1;
    } else {
      line[len - 1] = '\0';
      strncpy(p, line, len);
      lineptr[nlines++] = p;
    }
  }

  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  int i;

  for (i = 0; i < nlines; i++) {
    printf("%s\n", lineptr[i]);
  }
}

void quick_sort(void *v[], int left, int right,
                int (*comp)(const void *, const void *), int reverse) {
  int i, last;

  void swap(void *v[], int i, int j);

  if (left >= right) {
    return;
  }

  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    if (reverse ? (*comp)(v[i], v[left]) > 0 : (*comp)(v[i], v[left]) < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  quick_sort(v, left, last - 1, comp, reverse);
  quick_sort(v, last + 1, right, comp, reverse);
}

void swap(void *v[], int i, int j) {
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int numcmp(const char *s1, const char *s2) {
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);

  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  } else {
    return 0;
  }
}

int foldcmp(const char *s1, const char *s2) {
  for (; *s1 != '\0' && *s2 != '\0'; s1++, s2++) {
    int diff = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
    if (diff != 0) {
      return diff;
    }
  }
  return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}