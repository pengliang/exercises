#include <stdio.h>

enum ParserState {
  kStateOtherCharacters,
  kStateWhiteSpace
};

// Prints input one word per line
int main() {
  int current_char;
  enum ParserState state = kStateOtherCharacters;

  while ((current_char = getchar()) != EOF) {
    switch (state) {
      case kStateOtherCharacters:
        switch (current_char) {
          case ' ':
          case '\n':
          case '\t':
            putchar('\n');
            state = kStateWhiteSpace;
            break;
         default:
           putchar(current_char);
        }
        break;
      case kStateWhiteSpace:
        switch (current_char) {
          case ' ':
          case '\n':
          case '\t':
            break;
          default:
            state = kStateOtherCharacters;
            putchar(current_char);
        }
        break;
      default:
        break;
    }
  }
  return 0;
}

