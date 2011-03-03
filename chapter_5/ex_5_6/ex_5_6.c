/* ============pointer version of GetLine =======*/
#include <stdio.h>

/* Reads a line from input into s and return it's length
 *
 * @param s
 * @param lim max length of input can be read
 * @return the len read from input
 */
int GetLine(char *s, int lim) {
  int c;
  char *t = s;

  while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
    *s++ = c;
  }
  if (c == '\n') {
    *s++ = c;
  }
  *s = '\0';
  return s - t;
}

/* ==========pointer version of atoi==============*/
#include <ctype.h>

enum PaserState {
  kStart,
  kInteger
};

/* Coverts string s to integer; pointer version
 *
 * @param s
 * @return the integer converted from s
 */
int StringToInteger(char *s) {
  int n, sign;

  enum PaserState state = kStart;

  while (*s++ != '\0') {
    switch (state) {
      case kStart:
        if (isdigit(*s)) {
          n = 10 * n + (*s  - '0');
          state = kInteger;
        } else {
          switch (*s) {
            case ' ':
            case '\t':
            case '\n':
              break;
            case '-':
            case '+':
              sign = (*s == '-') ? -1 : 1;
              state = kInteger;
              break;
            default:
              return 0;
          }
        }
        break;
      case kInteger:
        if (isdigit(*s)) {
          n = 10 * n + (*s - '0');
        } else {
          return -1;
        }
        break;
    }
  }
  return n * sign;
}

/* ==========pointer version of itoa ============*/
#include <utils/reverse.h>

static char digit[] = "0123456789abcdef";

/* Converts integer n to characters in s
 *
 * @param n
 * @param s
 */
void IntegerToString(int n, char *s) {
  // Most left single numeric digit in integer n.
  int remain = 0;
  int sign = n;
  int base = 10;
  char *bs = s;

  if (sign < 0) {
    n = -n;
  }
  do {
    remain = n % base;
    *s++ = digit[remain];
  } while ((n /= base) != 0);
  if (sign < 0) {
    *s++ = '-';
  }
  *s = '\0';
  StringReverse(s, s - bs);
}
