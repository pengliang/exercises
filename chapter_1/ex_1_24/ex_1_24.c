#include <stdio.h>
#include "utils/stack.h"

const int kStackInitSize = 100;

static int col = 0, line = 1;

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

// Check the right bracket's matching.
//
// @param s, the stack's address.
// @param c, current character.
void CheckBrackets(Stack *s, char c);

// Remove all comments from a valid C program
int main() {
  // Current char.
  int c;
  // Open quote char, ' or "
  int quote_char;
  enum ParserState state = kNormalCode;
  Element top_element;
  Stack s;
  InitStack(&s, kStackInitSize);
  int block_comment_start_line =0;
  int block_comment_start_col = 0;

  while ((c = getchar()) != EOF) {
    ++col;
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
            break;
          case '\n':
            col = 0;
            ++line;
            break;
          default:
            CheckBrackets(&s, c);
            break;
        }
        break;
      case kLeadingSlash:
        switch (c) {
          case '*':
            state = kInBlockComment;
            block_comment_start_line = line;
            block_comment_start_col = col;
            break;
          case '/':
            state = kInLineComment;
            break;
          default:
            state = kNormalCode;
        }
        break;
      case kInQuotes:
        if (c == '\\') {
          state = kEscapeInQuotes;
        } else if (c == quote_char) {
          state = kNormalCode;
        } else if (c == '\n'){
          // Missmatch Quotation marks in this line.
          printf("line %d: error: missing terminating %c character.\n",
                 line, quote_char);
          ++line;
          state = kNormalCode;
        }
        break;
      case kEscapeInQuotes:
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
            ++line;
            break;
          default:
            break;
        }
        break;
    }
  }
  switch (state) {
    case kInBlockComment:
      printf("line %d, col %d: error: unterminated comment.\n",
              block_comment_start_line, block_comment_start_col);
      break;
    case kInQuotes:
      printf("line %d: error: missing terminating quote character.\n",
             line, c);
      break;
    default:
      break;
  }
  while (Pop(&s, &top_element)) {
    //Not Empty Stack
    printf("line %d, col %d: error: Missmatch for %c character.\n",
           top_element.line, top_element.col, top_element.c);
  }
  free(s.base);
  return 0;
}

void CheckBrackets(Stack *s, char c) {
  Element top_element;
  switch (c) {
    case '(':
    case '[':
    case '{':
      top_element.c = c;
      top_element.line = line;
      top_element.col = col;
      Push(s, &top_element);
      break;
    case ')':
      Pop(s, &top_element);
      if (top_element.c != '(') {
        printf("line %d, col %d: error: missmatch for %c character.\n",
               line, col, c);
      }
      break;
    case ']':
      Pop(s, &top_element);
      if (top_element.c != '[') {
        printf("line %d, col %d: error: missmatch for %c character.\n",
               line, col, c);
      }
      break;
    case '}':
      Pop(s, &top_element);
      if (top_element.c != '{') {
        printf("line %d, col %d: error: missmatch for %c character.\n",
               line, col, c);
      }
      break;
    default:
      break;
  }
}
