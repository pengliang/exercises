#include <stdio.h>

const int kTabSize = 8;

// Replace strings of blanks with the least tabs and blanks.
int main() {
  // Current char
  int c;
  // number of blanks neccessary
  int blanks = 0;
  // number of tabs neccessary
  int tabs = 0;
  // Current position
  int pos = 1;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      if (pos % kTabSize != 0) {
        ++blanks;
      } else {
        blanks = 0;
        ++tabs;
      }
    } else {
      for ( ; tabs > 0; --tabs) {
        putchar('\t');
      }
      if (c == '\t') {
        blanks = 0;
        pos += (kTabSize - (pos -1) % kTabSize) - 1;
      } else {
        for ( ; blanks > 0; --blanks) {
          putchar(' ');
        }
        if (c == '\n') {
          pos = 0;
        }
      }
      putchar(c);
      ++pos;
    }
  }
  return 0;
}
