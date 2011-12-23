#include <utils/string_reverse.h>

static char digit[] = "0123456789abcdef";

// Converts interger n to characters in s
//
// @param n integer
// @param s string converted from n
void IntegerToString(int n, char s[]) {
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
  s[i] = '\0';
  StringReverse(s, i);
}
