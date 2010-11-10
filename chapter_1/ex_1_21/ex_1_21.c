#include <stdio.h>

static const int kTabSize = 8;

// Flush the cached space_number on stdout.
//
// @param space_number cached space_number number.
static void FlushCachedSpaces(int space_number);

// Replace strings of space_number with the least tabs and space_number.
int main() {
  // Current char
  int c;
  // Current position
  int pos = 0;
  // number of space_number necessary
  int space_number = 0;

  while ((c = getchar()) != EOF) {
    switch (c) {
      case ' ':
        ++pos;
        if (pos % kTabSize != 0) {
          ++space_number;
        } else {
          // Reach a tab stop.
          space_number = 0;
          putchar('\t');
        }
        break;
      case '\t':
        // Forget the cached space_number.
        space_number = 0;
        pos += kTabSize - pos % kTabSize;
        putchar(c);
        break;
      case '\n':
        FlushCachedSpaces(space_number);
        space_number = 0;
        // Reset the position flag.
        pos = 0;
        putchar(c);
        break;
      default:
        FlushCachedSpaces(space_number);
        space_number = 0;
        putchar(c);
        ++pos;
    }
  }
  return 0;
}

static void FlushCachedSpaces(int space_number) {
  for (; space_number > 0; --space_number) {
    putchar(' ');
  }
}
