#include <syscall.h>

/* Sets file's position indicator for the file pointed to by fp.
 *
 * @param fp file pointer
 * @param offset new position's offset relative to origin.
 * @param origin origin position.
 * @return 0 for successful completion,
 *         -1 for otherwise.
 */
int fseek(FILE *fp, long offset, int origin) {
  int nc = 0, rc = 0;

  if (fp->flag & _READ) {
    if (origin == 1) {
      offset -= fp->cnt;
    }
    rc = lseek(fp->fd, offset, origin);
    fp->cnt = 0;
  } else if (fp->flag & _WRITE) {
    if ((nc = fp->ptr - fp->base) > 0) {
      if (write(fp->fd, fp->base, nc) != nc) {
        rc = -1;
      }
    }

    if (rc != -1) {
      rc = lseek(fp->fd, offset, origin);
    }
  }

  return (rc == -1) ? -1 : 0;
}
