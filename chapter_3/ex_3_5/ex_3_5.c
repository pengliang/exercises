#include "utils/string_reverse.h"

static char digit[] = "0123456789abcdef";

// Converts integer n to characters in string s base b.
//
// @param n integer digit.
// @param s stirng converted from digit.
// @param b the base used.
void IntegerToString(int n, char s[], int base) {
  int i = 0;
  // Most left single numeric digit in integer n.
  int remain = 0;
  int sign = n;

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
  s[i] = '\0';
  StringReverse(s, i);
}
