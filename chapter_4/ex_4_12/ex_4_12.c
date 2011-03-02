#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "utils/string_reverse.h"

/* Converts integer n to characters in s recursivly. */
void ItoaInternal(int n, char s[], int i) {
  if (n / 10) {
    ItoaInternal(n / 10, s, i + 1);
  } else {
    if (n < 0) {
      s[i++] = '-';
    }
    s[i + 1] = '\0';
  }
  s[i] = abs(n) % 10 + '0';
}

/* Converts integer n to characters in s*/
char *itoa(int n, char *s) {
  ItoaInternal(n, s, 0);
  StringReverse(s, strlen(s));
  return s;
}
