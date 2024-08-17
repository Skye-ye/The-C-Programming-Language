i = 0;
for (;;) {
  if (i >= lim - 1) break;

  c = getchar();
  if (c == '\n') break;
  if (c == EOF) break;
  
  s[i] = c;
  ++i;
}
