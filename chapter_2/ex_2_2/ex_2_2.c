#include <stdio.h>

// An style without && and || operator for next program.
// for (i = 0; i < lim - 1; && (c = getchar()) != '\n' && c! = EOF; ++i) {
//   s[i] = c;
// }
int main() {
  int c, i = 0, lim = 10;
  char s[lim];

  for (i  = 0; i < lim -1; ++i) {
    c = getchar();
    if (c == '\n') {
      break;
    } else if (c == EOF) {
      break;
    } else {
      s[i] = c;
    }
  }
  return 0;
}

