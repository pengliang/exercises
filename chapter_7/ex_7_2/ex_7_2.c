#include <stdio.h>
#include <ctype.h>

static const int kMaxLine = 80;
static const int kOctLen = 6;

/* Prints arbitrary input in a sensible way. */
int main() {
  int c, pos = 0;

  while ((c = getchar()) != EOF) {
    if (iscntrl(c) || c == ' ') {
      printf(" \\%03o ", c);
      if ((pos += kOctLen) >= kMaxLine) {
        putchar('\n');
        pos = kOctLen;
      }

      if (c == '\n') {
        pos = 0;
        putchar(c);
      }
    } else {
      putchar(c);
      if (pos++ >= kMaxLine) {
        putchar('\n');
        pos = 1;
      }
    }
  }
}
