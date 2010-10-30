#include "utils/string_reverse.h"

// Convert n to characters in string s base b.
//
// @param n, integer digit.
// @param s, stirng converted from digit.
// @param b, the base used.
void IntegerToString(int n, char s[], int b) {
  int i = 0, j = 0, sign = n;

  do {
    j = n % b;
    j = (j < 0)? -j : j;
    s[i++] = (j <= 9)? j + '0' : j + 'a' - 10;
  } while ((n /= b) != 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  StringReverse(s);
}

