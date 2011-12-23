#include "get_token.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

/* Gets next token from user's input
 *
 * @param token[out] buffer to store the token
 * @return an integer to indicate the token's type
 */
int GetToken(char *token) {
  int c;
  int len = 0;
  enum TokenType type = kBegin;

  memset(token, 0, strlen(token));

  while ((c = getchar()) != EOF) {
    switch (type) {
      case kBegin:
        switch (c) {
          case ' ':
          case '\t':
          case '\n':
            break;
          case '(':
            *token++ = c;
            type = kParens;
            break;
          case '[':
            *token++ = c;
            type = kBrackets;
            break;
          default:
            *token++ = c;
            if (isalpha(c)) {
              ++len;
              type = kName;
            } else {
              return c;
            }
            break;
        }
        break;
      case kParens:
        if (c == ')') {
          *token++ = c;
          return kParens;
        } else {
          ungetc(c, stdin);
          return '(';
        }
        break;
      case kBrackets:
        if ((*token++ = c) == ']') {
          return kBrackets;
        }
        break;
      case kName:
        if (isalnum(c)) {
          if (++len > kMaxToken) {
            Error("too long token");
          }
          *token++ = c;
        } else {
          ungetc(c, stdin);
          return kName;
        }
        break;
    }
  }
  return EOF;
}
