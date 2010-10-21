#include <stdio.h>
#include "utils/stack.h"

const int kStackInitSize = 100;
const int kSingleLineComments = 2;
const int kMultiLineComments = 1;

// Check the match of quotation, include ' and " and move out.
//
// @param c, quotation mark character, ' or ".
void CheckQuotations(char c);
// Check the comments and move out, including single line comment
// and mutiple line comment.
//
// @param comments_type, 1 for multiple line and 2 for single line.
void CheckComments(int comments_type);
// Check the right bracket's matching.
//
// @param s, the stack's address.
// @param c, current character.
void CheckBrackets(Stack *s, char c);

int col = 1, row = 1;

int main() {
  char c, nc;
  Element top_element;
  Stack s;
  InitStack(&s, kStackInitSize);
  while ((c = getchar()) != EOF) {
    ++col;

    switch (c) {
      case '\'':
      case '"':
        CheckQuotations(c);
        break;
      case '/':
        // Move out of comments.
        ++col;
        if ((nc = getchar()) == '*') {
          CheckComments(kMultiLineComments);
        } else if (nc == '/') {
          CheckComments(kSingleLineComments);
        } else {
          CheckBrackets(&s, nc);
        }
       break;
      case '\n':
        col = 0;
        ++row;
        break;
      default:
        CheckBrackets(&s, c);
        break;
    }
  }
  while (Pop(&s, &top_element)) {
    //Not Empty Stack
    printf("line %d, col %d: error: Missmatch for %c character.\n",
           top_element.row, top_element.col, top_element.c);
  }
  return 0;
}

void CheckQuotations(char c) {
  int nc;
  ++col;
  while ((nc = getchar()) != c) {
    ++col;
    if (nc == '\\') {
      // Ignore the escape squence.
      ++col;
      getchar();
      } else if (nc == '\n' || nc == EOF) {
        // Missmatch Quotation marks in this line.
        printf("line %d: error: missing terminating %c character.\n",
               row, c);
        ++row;
        col = 0;
        break;
      }
  }
}

void CheckComments(int comments_type) {
  int cc, prev_c, comment_start_line = row, comment_start_col = col - 1;
  if (comments_type == kMultiLineComments) {
    // In /* ... */ style comments, find the end tag.
    ++col;
    cc = getchar();
    ++col;
    while ((prev_c = cc) != '*' | (cc = getchar()) != '/') {
      ++col;
      if (prev_c == '\n') {
        ++row;
        col = 1;
      }
      if (cc ==  '\n') {
        ++row;
        col = 0;
      }
      if (cc == EOF || prev_c == EOF) {
        printf("line %d, col %d: error: unterminated comment.\n",
               comment_start_line, comment_start_col);
        break;
      }
    }
  } else {
    // In // style comments, just move to next line.
    while ((cc = getchar()) != '\n') {}
    ++row;
    col = 0;
  }
}

void CheckBrackets(Stack *s, char c) {
  Element top_element;
  switch (c) {
    case '(':
    case '[':
    case '{':
      top_element.c = c;
      top_element.row = row;
      top_element.col = col;
      Push(s, &top_element);
      break;
    case ')':
    case ']':
    case '}':
      Pop(s, &top_element);
      int sum = top_element.c + c;
      if (sum != 81 && sum != 184 && sum != 248) {
        printf("line %d, col %d: error: missmatch for %c character.\n",
               row, col, c);
      }
      break;
   default:
      break;
  }
}
