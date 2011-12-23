#include <string.h>
#include "utils/string_reverse.h"

static char digit[] = "0123456789abcdef";

// Converts integer n to characters in string s, at least w wide.
//
// @param n integer digit.
// @param s string buffer.
// @param w minimal width of s.
void IntegerToString(int n, char s[], int w) {
  int i = 0;
  // Most left single numeric digit in integer n.
  int remain = 0;
  int sign = n;
  int base = 10;

  if (sign < 0) {
    n = -n;
  }
  do {
    remain = n % base;
    s[i++] = digit[remain];
  } while ((n /= base) != 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  if (i < w) {
    memset(s + i, ' ', w - i);
    s[w] = '\0';
    i = w;
  } else {
    s[i] = '\0';
  }
  StringReverse(s, i);
}
