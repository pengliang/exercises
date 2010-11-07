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
  // In block comment, /* ... */
  kInBlockComment,
  // In line comment, start with //
  kInLineComment,
  // IN single quotation, begin with '
  kInSingleQuotation,
  // In double quotation, begin with "
  kInDoubleQuotation,
  // Found a escape in quotations
  kEscapeInSingleQuotation,
  kEscapeInDoubleQuotation
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
  enum ParserState state = kNormalCode;
  Element top_element;
  Stack s;
  StackInit(&s, kStackInitSize);
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
            state = kInSingleQuotation;
            break;
          case '"':
            state = kInDoubleQuotation;
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
      case kInSingleQuotation:
        switch (c) {
          case '\\':
            state = kEscapeInSingleQuotation;
            break;
          case '\'':
            state = kNormalCode;
            break;
          case '\n':
            // Miss match Quotation marks in this line.
            printf("line %d: error: missing terminating ' character.\n",
                   line);
            ++line;
            state = kNormalCode;
            break;
          default:
            break;
        }
        break;
      case kInDoubleQuotation:
        switch (c) {
          case '\\':
            state = kEscapeInDoubleQuotation;
            break;
          case '"':
            state = kNormalCode;
            break;
          case '\n':
            // Miss match Quotation marks in this line.
            printf("line %d: error: missing terminating \".\n",
                   line);
            ++line;
            state = kNormalCode;
            break;
          default:
            break;
        }
        break;
      case kEscapeInSingleQuotation:
        state = kInSingleQuotation;
        break;
      case kEscapeInDoubleQuotation:
        state = kInDoubleQuotation;
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
    case kInSingleQuotation:
      printf("line %d: error: missing terminating ' character.\n",
             line);
      break;
    case kInDoubleQuotation:
      printf("line %d: error: missing terminating \" character.\n",
             line);
      break;
    default:
      break;
  }
  while (StackPop(&s, &top_element)) {
    //Not Empty Stack
    printf("line %d, col %d: error: miss match for %c character.\n",
           top_element.line, top_element.col, top_element.c);
  }
  StackDestroy(&s);
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
      StackPush(s, &top_element);
      break;
    case ')':
      StackPop(s, &top_element);
      if (top_element.c != '(') {
        printf("line %d, col %d: error: miss match for %c character.\n",
               line, col, c);
      }
      break;
    case ']':
      StackPop(s, &top_element);
      if (top_element.c != '[') {
        printf("line %d, col %d: error: miss match for %c character.\n",
               line, col, c);
      }
      break;
    case '}':
      StackPop(s, &top_element);
      if (top_element.c != '{') {
        printf("line %d, col %d: error: miss match for %c character.\n",
               line, col, c);
      }
      break;
    default:
      break;
  }
}
