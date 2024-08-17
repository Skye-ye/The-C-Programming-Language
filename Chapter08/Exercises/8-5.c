#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define MAX_PATH 1024

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));
void print_permissions(mode_t mode);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fsize(".");
  } else {
    while (--argc > 0) {
      fsize(*++argv);
    }
  }
  return 0;
}

void fsize(char *name) {
  struct stat stbuf;
  struct passwd *pwd;
  struct group *grp;

  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }
  if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
    dirwalk(name, fsize);
  }

  pwd = getpwuid(stbuf.st_uid);
  grp = getgrgid(stbuf.st_gid);

  printf("File: %s\n", name);
  printf("Size: %lld bytes\n", (long long)stbuf.st_size);
  printf("Blocks: %lld\n", (long long)stbuf.st_blocks);
  printf("IO Block: %ld bytes\n", (long)stbuf.st_blksize);
  printf("Inode: %llu\n", (unsigned long long)stbuf.st_ino);
  printf("Links: %lu\n", (unsigned long)stbuf.st_nlink);
  printf("Access: ");
  print_permissions(stbuf.st_mode);
  printf("\n");
  printf("Uid: (%d/%s)\n", stbuf.st_uid, pwd ? pwd->pw_name : "unknown");
  printf("Gid: (%d/%s)\n", stbuf.st_gid, grp ? grp->gr_name : "unknown");
  printf("Access: %s", ctime(&stbuf.st_atime));
  printf("Modify: %s", ctime(&stbuf.st_mtime));
  printf("Change: %s", ctime(&stbuf.st_ctime));
  printf("\n");
}

void dirwalk(char *dir, void (*fcn)(char *)) {
  char name[MAX_PATH];
  struct dirent *dp;
  DIR *dfd;

  if ((dfd = opendir(dir)) == NULL) {
    fprintf(stderr, "dirwalk: can't open %s\n", dir);
    return;
  }
  while ((dp = readdir(dfd)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
      continue;
    }
    if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
      fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
    } else {
      sprintf(name, "%s/%s", dir, dp->d_name);
      (*fcn)(name);
    }
  }
  closedir(dfd);
}

void print_permissions(mode_t mode) {
  printf((S_ISDIR(mode)) ? "d" : "-");
  printf((mode & S_IRUSR) ? "r" : "-");
  printf((mode & S_IWUSR) ? "w" : "-");
  printf((mode & S_IXUSR) ? "x" : "-");
  printf((mode & S_IRGRP) ? "r" : "-");
  printf((mode & S_IWGRP) ? "w" : "-");
  printf((mode & S_IXGRP) ? "x" : "-");
  printf((mode & S_IROTH) ? "r" : "-");
  printf((mode & S_IWOTH) ? "w" : "-");
  printf((mode & S_IXOTH) ? "x" : "-");
}