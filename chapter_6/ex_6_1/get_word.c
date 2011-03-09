#include "get_word.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum ParserState {
  kBegin,
  // Found a valid word
  kWord,
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
  // Found a escape in quotes
  kEscapeInQuotes
};

/* Skips the comments after the "/*" or "//".
 *
 * @param state indicates beginning status:
 *              kInBlockComment for block comment,
 *              kInLineComment for line comment.
 * @return '/' for finding the end of comments
 *         EOF(-1) for otherwise
 */
static int SkipComments(enum ParserState state);

/* Skips the string quoted by ' or " from the first char of string.
 *
 * @param quote_char must be ' or " char
 * @return quote_char for finding the end of quote string
 *         EOF(-1) for otherwise
 */
static int SkipQuoteString(int quote_char);

/* Gets next word or character from input */
int GetWord(char *word, int max_word_len) {
  int c, len = max_word_len;
  int quote_char;
  char *p = word;

  enum ParserState state = kBegin;

  memset(word, 0, len);

  while ((c = getchar()) != EOF) {
    switch (state) {
      case kBegin:
        switch (c) {
          case ' ':
          case '\t':
            break;
          case '/':
            state = kLeadingSlash;
            break;
          case '\'':
          case '"':
            state = kInQuotes;
            quote_char = c;
            break;
          default:
            *p++ = c;
            if (isalpha(c) || c == '_' || c == '#') {
              state = kWord;
            } else {
              return c;
            }
        }
        break;
      case kWord:
        if (p - word < len) {
          if (isalnum(c) || c == '_') {
            *p++ = c;
          } else {
            ungetc(c, stdin);
            return 1;
          }
        } else {
          printf("Error: too long word.");
          exit(1);
        }
        break;
      case kLeadingSlash:
        switch (c) {
          case '*':
            if ('/' == SkipComments(kInBlockComment)) {
              state = kBegin;
            } else {
              printf("Error: missing end sign of block comment");
              return EOF;
            }
            break;
          case '/':
            if ('\n' == SkipComments(kInLineComment)) {
              state = kBegin;
            } else {
              return EOF;
            }
            break;
          default:
            state = kBegin;
            ungetc(c, stdin);
            return '/';
        }
        break;
      case kInQuotes:
        if (quote_char == SkipQuoteString(quote_char)) {
          state = kBegin;
        } else {
          return EOF;
        }
        break;
     }
  }
  return EOF;
}

static int SkipComments(enum ParserState state) {
  int c;

  while ((c = getchar()) != EOF) {
    switch (state) {
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
            return c;
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
            return c;
          default:
            break;
        }
        break;
      default:
        return EOF;
    }
  }
  return EOF;
}

static int SkipQuoteString(int quote_char) {
  int c;
  enum ParserState state = kInQuotes;

  while ((c = getchar()) != EOF) {
    switch (state) {
      case kInQuotes:
        if (c == quote_char) {
          return c;
        }
        if (c == '\\') {
          state = kEscapeInQuotes;
        }
        break;
      case kEscapeInQuotes:
        state = kInQuotes;
        break;
      default:
        return EOF;
    }
  }
  return EOF;
}
