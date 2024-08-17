char *strncpy(char *s, char *ct, size_t n) {
  char *cs;
  cs = s;

  while (n-- > 0 && (*s++ = *ct++) != '\0') {
    ;
  }

  return cs;
}

char *strncat(char *s, char *ct, size_t n) {
  char *cs;
  cs = s;

  while (*s != '\0') {
    s++;
  }

  while (n-- > 0 && (*s++ = *ct++) != '\0') {
    ;
  }

  *s = '\0';

  return cs;
}

int strncmp(char *cs, char *ct, size_t n) {
  for (; n > 0 && *cs == *ct; cs++, ct++, n--) {
    if (*cs == '\0') {
      return 0;
    }
  }

  return *cs - *ct;
}