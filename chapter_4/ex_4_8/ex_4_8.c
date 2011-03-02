#include <stdio.h>

static char buf = EOF;

/* Gets a character */
int getch() {
  unsigned char c;

  if (buf != EOF) {
    c = buf;
  } else {
    c = getchar();
  }
  buf = EOF;
  return c;
}

/* Pushes a character back onto the input */
void ungetch(unsigned char c) {
  if (buf != EOF) {
    printf("ungetch: too many characters\n");
  } else {
    buf = c;
  }
}
