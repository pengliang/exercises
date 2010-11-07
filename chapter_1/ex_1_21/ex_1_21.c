#include <stdio.h>

const int kTabSize = 8;
// number of spaces necessary
static int spaces = 0;
// number of tabs necessary
static int tabs = 0;

// Flush the cached tabs on stdout.
void FlushCachedTabs();

// Flush the cached spaces on stdout.
void FlushCachedSpaces();

// Replace strings of spaces with the least tabs and spaces.
int main() {
  // Current char
  int c;
  // Current position
  int pos = 0;

  while ((c = getchar()) != EOF) {
    switch (c) {
      case ' ':
        if (pos % kTabSize != 0) {
          ++spaces;
        } else {
          // Reach a tab stop.
          spaces = 0;
          ++tabs;
        }
        break;
      case '\t':
        FlushCachedTabs();
        // Forget the cached spaces.
        spaces = 0;
        pos += kTabSize - pos % KTabSize;
        putchar(c);
        break;
      case '\n':
        FlushCachedTabs();
        FlushCachedSpaces();
        // Reset the position flag.
        pos = 0;
        putchar(c);
        break;
      default:
        FlushCachedTabs();
        FlushCachedSpaces();
        putchar(c);
        ++pos;
    }
  }
  return 0;
}

void FlushCachedTabs() {
  for (; tabs > 0; --tabs) {
    putchar('\t');
  }
}

void FlushCachedSpaces() {
  for (; spaces > 0; --spaces) {
    putchar(' ');
  }
}
