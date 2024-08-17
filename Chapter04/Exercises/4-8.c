int getch(void) {
  static int buf = EOF;
  int c;

  if (buf != EOF) {
    c = buf;
    buf = EOF;
  } else {
    c = getchar();
  }

  return c;
}

void ungetch(int c) {
  static int buf = EOF;

  if (buf != EOF) {
    printf("ungetch: too many characters\n");
  } else {
    buf = c;
  }
}