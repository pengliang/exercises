#include <stdio.h>

// print input one word pre line
int main() {
  int current_char;
  int state = 0;  // status flag

  while ((current_char = getchar()) != EOF) {
    if (current_char == ' ' || current_char == '\n' || current_char == '\t') {
      if (state == 1) {
        putchar('\n');  // finish a word
        state = 0;
      }
    } else if (state == 0) {
      state = 1;
      putchar(current_char);
    } else {
      putchar(current_char);
    }
  }
  return 0;
}

