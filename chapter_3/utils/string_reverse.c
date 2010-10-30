#include "string_reverse.h"

void StringReverse(char s[]) {
  int i = 0, j = 0;
  while (s[i++] != '\0') {}
  for(i -= 2, j = 0; j < i; ++j, --i) {
    char temp;
    temp = s[j];
    s[j] = s[i];
    s[i] = temp;
  }
}
