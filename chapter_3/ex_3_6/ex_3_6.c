// Convert integer n to characters in string s, at least w wide.
//
// @param n, integer digit.
// @param s, string buffer.
// @param w, minimal width of s.
void IntegerToString(int n, char s[], int w) {
  int i = 0, j = 0, sign = n;
  int base = 10;

  do {
    j = n % base
    j = (j < 0)? -j : j;
    s[i++] = j + '0';
  } while ((n /= base) != 0);
  if (sign < 0) {
    s[i++] = '-';
  }
  while (i < w) {
    s[i++] = ' ';
  }
  s[i] = '\0';
  StringReverse(s);
}
