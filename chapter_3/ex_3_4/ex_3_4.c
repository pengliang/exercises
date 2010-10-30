#include <utils/string_reverse.h>

// Convert n to characters in s
//
// @param n, integer
// @param s, string converted from n
void IntegerToString(int n, char s[]) {
  int i = 0, j = 0, sign = n;

  do {
    j = n % 10;
    j = (j < 0)? -j : j;
    s[i++] = j + '0';
  } while ((n /= 10) != 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  s[i] = '\0';
  StringReverse(s);
}
