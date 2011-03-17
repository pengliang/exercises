#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum PaserState {
  kStart,
  kInteger
};

int StrToInt(const char *s, int *value) {
  int n = 0, sign = 1;

  enum PaserState state = kStart;

  if (*s == '\0') {
    return 0;
  }

  while (*s != '\0') {
    switch (state) {
      case kStart:
        if (isdigit(*s)) {
          n = 10 * n + (*s  - '0');
          state = kInteger;
        } else {
          switch (*s) {
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
          return 0;
        }
        break;
    }
    ++s;
  }
  *value = n * sign;
  return 1;
}


static char digit[] = "0123456789abcdef";

char *IntToStr(int n, char *s) {
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
  s = StringReverse(bs, s - bs);

  return s;
}

char *StringReverse(char *s, int n) {
  int i = 0, j = 0;
  for(i = n - 1, j = 0; j < i; ++j, --i) {
    char temp;
    temp = s[j];
    s[j] = s[i];
    s[i] = temp;
  }
  return s;
}

char *SubStr(const char *str, int from, int to) {
  char *result = NULL;
  int str_len = 0, sub_len = 0;

  str_len = strlen(str);

  if (!(from >= 0 && from <= to && to <= str_len)) {
    return strdup(str);
  }

  sub_len = to - from;
  result = malloc((sub_len + 1) * sizeof(*result));

  if (result) {
    strncpy(result, str + from, sub_len);
    result[sub_len] = '\0';
  }

  return result;
}
