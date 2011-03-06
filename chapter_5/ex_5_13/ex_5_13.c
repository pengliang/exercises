#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/get_line.h"

// Default number of lines to print
static const int kDefaultLines = 10;
// Max number of lines to print
static const int kMaxLines = 100;
// Max length of an input line
static const int kMaxLen = 10;

/* Prints last n lines of the input */
int main(int argc, char *argv[]) {
  char *p, *buf, *bufend;
  char line[kMaxLen];
  char *line_ptr[kMaxLines];

  int i = 0, last = 0, len = 0 , n = 0, nlines = 0;

  if (argc == 1) {
    n = kDefaultLines;
  } else if (argc == 2 && (*++argv)[0] == '-') {
    n = atoi(argv[0] + 1);
  } else {
    printf("Usage: tail [-n]");
    exit(1);
  }

  if (n < 1 || n > kMaxLines) {
    n = kMaxLines;
  }

  memset(line_ptr, 0, kMaxLines);

  if ((buf = malloc(n * kMaxLen)) == NULL) {
    printf("Error: can not allocate buf!");
    exit(1);
  }
  bufend = buf +  n * kMaxLen;

  p = buf;
  while ((len = GetLimitedLine(line, kMaxLen)) > 0) {
    if (len >= kMaxLen) {
      len = kMaxLen;
      // End the line
      line[len - 1] = '\0';
    }
    /* buffer wrap arround*/
    if (p + len > bufend) {
      memmove(bufend - p + buf, buf, p - buf);
      for (i = 0; i < n; ++i) {
        line_ptr[i] += bufend - p;
      }
      p = buf;
    }
    line_ptr[last] = p;
    memcpy(line_ptr[last], line, len);
    if (++last >= n) {
      last = 0;
    }
    p += len;
    ++nlines;
  }

  if (n > nlines) {
    n = nlines;
  }
  last = n;
  for (i = (nlines - n) % n; n-- > 0; i = (i + 1) % last) {
    printf("%s\n", line_ptr[i]);
  }
  return 0;
}
