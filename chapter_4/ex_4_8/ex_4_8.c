#include <stdio.h>

static char buf = 0;

/* Gets a character */
int getch() {
  int c;

  if (buf != 0) {
    c = buf;
  } else {
    c = getchar();
  }
  buf = 0;
  return c;
}

/* Pushes a character back onto the input */
void ungetch(int c) {
  if (buf != 0) {
    printf("ungetch: too many characters\n");
  } else {
    buf = c;
  }
}
