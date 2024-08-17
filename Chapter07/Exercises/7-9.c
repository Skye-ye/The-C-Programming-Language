int isupper_save_space(int ch) { return ch >= 'A' && ch <= 'Z'; }

static const char bits[257] = {... initialization...};

int isupper_save_time(int ch) {
  assert(ch == EOF || (ch >= 0 && ch <= 255));
  return ((bits + 1)[ch] & UPPER_MASK);
}