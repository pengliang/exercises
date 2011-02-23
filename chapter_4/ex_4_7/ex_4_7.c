#include <stdio.h>
#include <string.h>

#define Buf_Size 100

// buffer for ungetch
static char buf[Buf_Size];
// next free position in buf
static int bufp = 0;

/* Gets a character */
int getch() {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Pushes a character back onto the input */
void ungetch(int c) {
  if (bufp >= Buf_Size) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}

/* Pushes string back onto the input */
void ungets(char s[]) {
  int i = 0;
  int len  = strlen(s);
  for (i = len; i > 0; i--) {
    ungetch(s[i]);
  }
}


