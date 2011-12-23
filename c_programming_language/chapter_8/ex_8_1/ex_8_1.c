#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syscall.h>

/* Copys the file refered to by file descriptor i_fd to
 * another file refered to by o_fd.
 *
 * @param i_fd source file's descriptor
 * @param o_fd dest file's descriptor
 */
void CopyFile(int i_fd, int o_fd);

/* Concatenates files on stdout */
int main(int argc, char *argv[]) {
  int fd;

  if (argc == 1) {
    CopyFile(0, 1);
  } else {
    while (--argc > 0) {
      if ((fd = open(*++argv, O_RDONLY)) == -1) {
        printf("Error: can't open file %s\n", *argv);
        exit(1);
      } else {
        CopyFile(fd, 1);
        close(fd);
      }
    }
  }
  return 0;
}

void CopyFile(int i_fd, int o_fd) {
  int n;
  char buf[BUFSIZ];

  while ((n = read(i_fd, buf, BUFSIZ)) > 0) {
    if (write(o_fd, buf, n) != n) {
      printf("Error: write error.\n");
      exit(1);
    }
  }
}
