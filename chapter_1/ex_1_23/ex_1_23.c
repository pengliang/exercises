#include <stdio.h>

enum ParserState {
  // Parsing Normal code
  kNormalCode,
  // Found a leading slash '/'
  kLeadingSlash,
  // Found a trailing star '*' in a block comment
  kTrailingStar,
  // In a block comment, /* ... */
  kInBlockComment,
  // In a line comment, start with //
  kInLineComment,
  // IN a quotation, begin with ' or "
  kInQuotes,
  // FOund a escape in quotes
  kEscapeInQuotes
};

// Remove all comments from a valid C program
int main() {
  // Current char.
  int c;
  // Record the open quote char.
  int quote_char;
  enum ParserState state = kNormalCode;

  while ((c = getchar()) != EOF) {
    switch (state) {
      case kNormalCode:
        switch (c) {
          case '/':
            state = kLeadingSlash;
            break;
          case '\'':
          case '"':
            state = kInQuotes;
            quote_char = c;
            putchar(c);
            break;
          default:
            putchar(c);
        }
        break;
      case kLeadingSlash:
        switch (c) {
          case '*':
            state = kInBlockComment;
            break;
          case '/':
            state = kInLineComment;
            break;
          default:
            state = kNormalCode;
            putchar('/');
            putchar(c);
        }
        break;
      case kInQuotes:
        if (c == '\\') {
          state = kEscapeInQuotes;
        } else if (c == quote_char) {
          state = kNormalCode;
          putchar(c);
        } else {
          putchar(c);
        }
        break;
      case kEscapeInQuotes:
        putchar(c);
        state = kInQuotes;
        break;
      case kInBlockComment:
        switch (c) {
          case '*':
            state = kTrailingStar;
            break;
          default:
            break;
        }
        break;
      case kTrailingStar:
        switch (c) {
          case '/':
            state = kNormalCode;
            break;
          case '*':
            state = kTrailingStar;
          default:
            state = kInBlockComment;
            break;
        }
        break;
      case kInLineComment:
        switch (c) {
          case '\n':
            state = kNormalCode;
            putchar('\n');
            break;
          default:
            break;
        }
        break;
    }
  }
  return 0;
}
