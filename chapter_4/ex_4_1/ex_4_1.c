// Return most right index of string t in string s, -1 if nons.
// Forward version.
//
// @param s, source string buffer.
// @param t, template substring.
int StrRIndexForward(char s[], char t[]) {
  int i = 0, j = 0, k = 0, rightest_index = -1;

  for (i = 0; s[i] != '\0'; i++) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k) {}
    if (k > 0 && t[k] == '\0') {
      rightest_index = i + 1;
    }
  }
  return rightest_index;
}

// Backward version.
//
// @param s, source string
// @param n, length of source string
// @param t, template string
// @param m, length of template string
int StrRIndexBackward(char s[], int n, char t[], int m) {
  int i = 0, j = 0, k = 0;
  for (i = n - m; i >= 0; --i) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) {}
    if (k > 0 && t[k] == '\0') {
      return i + 1;
    }
  }
  return -1;
}

const int WordLength = 32;
const int CharSet = 255;

//Shift-Or Algorithm
//
// @param s, source string
// @param n, length of source string
// @param t, template string
// @param m, length of template string
int StrRIndexShiftOr(char s[], int n, char t[], int m) {
  unsigned int b[CharSet], mask = 1, lim = 0;
  int i = 0, j = 0;
  unsigned int state = ~0;

  if (m > WordLength) {
    error("Template size should be <= machine's word length, here is 32.");
  }
  // Init the mask table.
  for (i = 0; i < CharSet; ++i) {
      b[i] = ~0;
  }
  for (i = m - 1, mask = 1; i >= 0 ; --i, mask <<= 1) {
    b[t[i]] &= ~mask;
    lim |= mask;
  }
  lim = ~(lim >> 1);

  // Search the substring backward.
  for (j = n -1; j >= 0; --j) {
    state  = (state << 1) | b[s[j]];
    if (state < lim) {
      return j + 1;
    }
  }
  return -1;
}
