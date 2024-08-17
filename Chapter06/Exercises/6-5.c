#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

char *str_dup(char *);

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void undef(char *);
void free_hashtab(void);

int main() {
  struct nlist *np;

  install("foo", "bar");
  install("baz", "qux");
  install("foo", "baz");

  np = lookup("foo");
  printf("%s\n", np->defn);

  np = lookup("baz");
  printf("%s\n", np->defn);

  undef("foo");
  np = lookup("foo");
  if (np == NULL) {
    printf("foo is not found\n");
  }

  free_hashtab();

  return 0;
}

char *str_dup(char *s) {
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL) strcpy(p, s);
  return p;
}

unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++) hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0) return np;
  return NULL;
}

struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) {
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = str_dup(name)) == NULL) return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else {
    free((void *)np->defn);
  }

  if ((np->defn = str_dup(defn)) == NULL) return NULL;
  return np;
}

void undef(char *name) {
  struct nlist *np, *prev;
  unsigned hashval;
  prev = NULL;

  hashval = hash(name);
  for (np = hashtab[hashval]; np != NULL; np = np->next) {
    if (strcmp(name, np->name) == 0) {
      if (prev != NULL) {
        prev->next = np->next;
      } else {
        hashtab[hashval] = np->next;
      }
      free(np->name);
      free(np->defn);
      free(np);
      return;
    }
    prev = np;
  }
}

void free_hashtab(void) {
  struct nlist *np, *temp;

  for (int i = 0; i < HASHSIZE; i++) {
    np = hashtab[i];
    while (np != NULL) {
      temp = np->next;
      free(np->name);
      free(np->defn);
      free(np);
      np = temp;
    }
    hashtab[i] = NULL;
  }
}
