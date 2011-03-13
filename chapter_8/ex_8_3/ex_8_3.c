#include <stdlib.h>
#include <syscall.h>

#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf {
  int cnt;
  char *ptr;
  char *base;
  int flag;
  int fd;
} FILE;

enum _flags {
  _READ = 01,
  _WRITE = 02,
  _UNBUF = 04,
  _EOF = 010,
  _ERR = 020
};

FILE _iob[OPEN_MAX] = {
  { 0, (char *) 0, (char *) 0, _READ, 0 },
  { 0, (char *) 0, (char *) 0, _WRITE, 1 },
  { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 },
};

/* Allocates or flushes output buffer, and
 * puts the new content x into the buffer.
 *
 * @param x new content
 * @param fp file pointer
 * @return x for successful completion
 *         EOF for oterwise.
 */
int _flushbuf(int x, FILE *fp) {
  int nc = 0;
  int buf_size;

  if (fp < _iob || fp >= _iob + OPEN_MAX) {
    return EOF;
  }

  if ((fp->flag & (_WRITE | _ERR)) != _WRITE) {
    return EOF;
  }

  buf_size = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

  if (fp->base == NULL) {
    if ((fp->base = malloc(buf_size)) == NULL) {
      fp->flag |= _ERR;
      return EOF;
    }
  } else {
    nc = fp->ptr - fp->base;
    if (write(fp->fd, fp->base, nc) != nc) {
      fp->flag |= _ERR;
      return EOF;
    }
  }

  fp->ptr = fp->base;
  *fp->ptr++ = (char) x;
  fp->cnt = buf_size - 1;
  return x;
}

/* Flushes buffer associated with file fp
 *
 * @param fp file pointer
 * @return 0 for successful completion,
 *         EOF for otherwise.
 */
int fflush(FILE *fp) {
  int rc = 0;

  if (fp < _iob || fp >= _iob + OPEN_MAX) {
    return EOF;
  }

  if (fp->flag & _WRITE) {
    rc = _flushbuf(0, fp);
  }
  fp->ptr = fp->base;
  fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

  return rc;
}

/* Closes the file fp
 *
 * @param fp file pointer
 * @return 0 for successful completion,
 *         EOF for otherwise.
 */
int fclose(FILE *fp) {
  int rc;

  if ((rc = fflush(fp)) != EOF) {
    free(fp->base);
    fp->ptr = NULL;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag &= ~(_READ | _WRITE);
  }

  return rc;
}
