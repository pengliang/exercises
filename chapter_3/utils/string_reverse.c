#include "string_reverse.h"

void StringReverse(char s[], int n) {
  int i = 0, j = 0;
  for(i = n - 1, j = 0; j < i; ++j, --i) {
    char temp;
    temp = s[j];
    s[j] = s[i];
    s[i] = temp;
  }
}
