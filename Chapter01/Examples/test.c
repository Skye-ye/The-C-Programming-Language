#include <stdio.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: ./test [your_name]\n");
    return -1;
  } else if (argc > 2) {
    printf("too many arguments\n");
    return 1;
  }

  printf("hello %s\n", argv[1]);

  return 0;
}
