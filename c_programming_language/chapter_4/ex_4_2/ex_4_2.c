#include <ctype.h>
#include <math.h>

// Converts string s to double. It can handle scientific notation
// of the form 123.45e-6, where a floating-point number may be followed
// by e or E and an optionally signed exponent.
//
// @param s string buffer.
// @return the double value converted from string
double String2Double(const char *s) {
  double val = 0.0;
  int exp = 0, power = 0, i = 0, sign = 1;

  // Skip white space
  for (i = 0; isspace(s[i]); ++i) {}

  sign = (s[i] == '-') ? -1 : 1;

  if (s[i] == '+' || s[i] == '-') {
    ++i;
  }
  for (val = 0.0; isdigit(s[i]); ++i) {
    val = 10.0 * val + (s[i] - '0');
  }
  if (s[i] == '.') {
    ++i;
  }
  for (power = 0; isdigit(s[i]); ++i) {
    val = 10.0 * val + (s[i] - '0');
    ++power;
  }
  val = sign * val;

  if (s[i] == 'e' || s[i] == 'E') {
    sign = (s[++i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
      ++i;
    }
    for (exp = 0; isdigit(s[i]); ++i) {
      exp = 10 * exp + (s[i] - '0');
    }
    val *= pow(10.0, sign * exp - power);
  }
  return val;
}
