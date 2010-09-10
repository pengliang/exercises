#include <stdio.h>

// count blanks, tabs and newlines
int main() {
  int c;  // input char
  int blanks = 0; // blank counter
  int tabs = 0; // tab counter
  int newlines = 0; // newline counter

  while ((c = getchar()) != EOF) {
    switch (c) {
      case ' ': {
         ++blanks;
         break;
      }
      case '\t': {
        ++tabs;
        break;
      }
      case '\b': {
        ++newlines;
        break;
      }
      default: {}
    }
  }
  printf("blanks: %d, tabs: %d, newlines: %d\n", blanks, tabs, newlines);
  return 0;
}
