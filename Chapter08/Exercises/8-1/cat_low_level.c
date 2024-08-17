#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1048576  // 1 MB buffer

void filecopy(int ifd, int ofd) {
  char *buf = malloc(BUFFER_SIZE);
  if (buf == NULL) {
    perror("malloc");
    exit(1);
  }

  ssize_t n;
  while ((n = read(ifd, buf, BUFFER_SIZE)) > 0) {
    char *ptr = buf;
    ssize_t nwritten;
    do {
      nwritten = write(ofd, ptr, n);
      if (nwritten <= 0) {
        if (nwritten < 0 && errno == EINTR)
          nwritten = 0;
        else {
          perror("write");
          free(buf);
          exit(1);
        }
      }
      n -= nwritten;
      ptr += nwritten;
    } while (n > 0);
  }

  if (n < 0) {
    perror("read");
    free(buf);
    exit(1);
  }

  free(buf);
}

int main(int argc, char *argv[]) {
  int fd;
  if (argc == 1) {
    filecopy(STDIN_FILENO, STDOUT_FILENO);
  } else {
    while (--argc > 0) {
      if ((fd = open(*++argv, O_RDONLY)) == -1) {
        perror(*argv);
        exit(1);
      } else {
        filecopy(fd, STDOUT_FILENO);
        if (close(fd) == -1) {
          perror("close");
          exit(1);
        }
      }
    }
  }
  return 0;
}