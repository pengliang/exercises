#include <stdio.h>

const int kTabSize = 8;

// Replace tabs with the proper number of blanks
int main() {
  // Current char
  int c;
  // Current posistion
  int pos = 0;
  // Number of blanks neccssary
  int blanks = 0;

  while ((c = getchar()) != EOF ) {
    switch (c) {
      case '\t':
        blanks = kTabSize - pos % kTabSize;
        for (; blanks > 0; --blanks) {
          putchar(' ');
          ++pos;
        }
        break;
      case '\n':
        putchar(c);
        pos = 0;
        break;
      default:
        putchar(c);
        ++pos;
    }
  }
  return 0;
}

