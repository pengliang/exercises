#include <stdio.h>

enum ParserState {
  kStateOtherCharacters,
  kStateWhiteSpace
};

// prints input one word pre line
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
      default: {}
    }
  }
  return 0;
}

