#include <stdio.h>

// copy input to output and replace each string of one or more blanks by a
// single blank.
int main() {
  int current_char;  // current position's char
  int previous_char = 'c';  // the char at previous position, default not blank

  while ((current_char = getchar()) != EOF) {
    if (current_char != ' ' || previous_char != ' ') {
      printf("%c", current_char);
    }
    previous_char = current_char;
  }
  return 0;
}
