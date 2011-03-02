#include <stdio.h>
#include <string.h>

#define BUF_SIZE 100

// buffer for ungetc, using integer array for EOF
static int buf[BUF_SIZE];
// next free position in buf
static int bufp = 0;

/* Gets a character */
int getch() {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Pushes a character back onto the input */
void ungetch(int c) {
  if (bufp >= BUF_SIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}
