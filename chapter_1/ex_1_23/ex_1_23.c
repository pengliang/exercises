#include <stdio.h>

// Remove all comments from a valid C program
int main() {
  // Current char and next char.
  int cc,nc;

  while ((cc = getchar()) != EOF) {
    switch (cc) {
      case '/':
        if ((nc = getchar()) == '*') {
          // In /* ... */ style comments, move out.
          nc = getchar();
          while ((cc = nc) != '*' | (nc = getchar()) != '/')) {}
        } else if (nc == '/') {
          // In // style comments, last character is '\n'
          while ((nc = getchar()) != '\n') {}
        } else {
          putchar(cc);
          if (nc != EOF) {
            putchar(nc);
          }
        }
        break;
      case '\'':
      case '"':
        // Echo characters within quotes, here is beginning.
        putchar(cc);
        while ((nc = getchar()) != cc) {
          putchar(nc);
          // ingore escape characters.
          if (nc == '\\') {
            putchar(getchar());
          }
        }
        // Here is the end.
        putchar(nc);
        break;
      default:
        // Not in comments and quotes, just output.
        putchar(cc);
    }
  }
  return 0;
}
