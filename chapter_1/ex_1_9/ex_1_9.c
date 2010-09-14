#include <stdio.h>

// Copy input to output and replace each string of one or more blanks by a
// single blank.
int main() {
  // Current position's char
  int current_char;
  // The char at previous position, default not blank
  int previous_char = 'c';

  while ((current_char = getchar()) != EOF) {
    if (current_char != ' ' || previous_char != ' ') {
      printf("%c", current_char);
    }
    previous_char = current_char;
  }
  return 0;
}
