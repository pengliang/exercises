#include <math.h>
#include <stdlib.h>

/* Converts integer n to characters in s recursivly. */
void itoa(int n, char s[])
{
  static int i;

  if (n / 10) {
    itoa(n / 10, s);
  } else {
    i = 0;
    if (n < 0) {
      s[i++] = '-';
    }
  }
  s[i++] = abs(n) % 10 + '0';
  s[i] = '\0';
}


