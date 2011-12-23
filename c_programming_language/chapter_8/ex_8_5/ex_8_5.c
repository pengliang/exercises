#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syscall.h>
#include <limits.h>

/* Applies function fcn to all files in dir
 *
 * @param dir directory path
 * @param fcn function pointer
 */
void dirwalk(char *dir, void (*fcn)(char *));

/* Prints inode number, mode, links, size of file
 *
 * @param name file name
 */
void fsize(char *name) {
  struct stat stbuf;

  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }

  if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
    dirwalk(name, fsize);
  }
  printf("%5ld %6o %3u %8ld %s\n", stbuf.st_ino, stbuf.st_mode,
         stbuf.st_nlink, stbuf.st_size, name);
}

void dirwalk(char *dir, void (*fcn)(char *)) {
  char name[FILENAME_MAX];
  struct dirent *dp;
  DIR *dfd;

  if ((dfd = opendir(dir)) == NULL) {
    fprintf(stderr, "dirwalk: can't open file %s\n", dir);
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
