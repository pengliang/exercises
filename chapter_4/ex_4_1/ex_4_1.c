// Finds the last occurrence of substring needle in the string
// haystack. Returns -1 if the substring is not found.
// Forward version.
//
// @param haystack source string.
// @param needle substring.
// @return the index of the last occurrence of the substring needle in the
//         string haystack, -1 if the substring is not found.
int StrRIndexForward(const char *haystack, const char *needle) {
  int i = 0, rightest_index = -1;

  if (needle[0] = '\0') {
    return -1;
  }

  for (i = 0; haystack[i] != '\0'; ++i) {
    int j = 0, k = 0;
    for (j = i, k = 0; needle[k] != '\0' && haystack[j] == needle[k];
         ++j, ++k) {}
    if (k > 0 && needle[k] == '\0') {
      rightest_index = i + 1;
    }
  }
  return rightest_index;
}

// Backward version.
//
// @param haystack source string
// @param n length of source string
// @param needle substring
// @param m length of substring
// @return the index of the last occurrence of the substring needle in the
//         string haystack, -1 if the substring is not found.
int StrRIndexBackward(const char *haystack, int n, const char *needle, int m) {
  int i = 0;

  if (needle[0] = '\0') {
    return -1;
  }

  for (i = n - m; i >= 0; --i) {
    int j = 0, k = m;
    for (j = i + m, k = m; haystack[j] == needle[k]; --j, --k) {}
    if (k == 0) {
      return i + 1;
    }
  }
  return -1;
}

#include <limits.h>
#include <stdio.h>

const int kWordLength = CHAR_BIT * sizeof(int);

//Shift-Or Algorithm
//
// @param haystack source string
// @param n length of source string
// @param needle substring
// @param m length of substring
// @return the index of the last occurrence of the substring needle in the
//         string haystack, -1 if the substring is not found.
int StrRIndexShiftOr(const char *haystack, int n, const char *needle, int m) {
  unsigned int b[UCHAR_MAX], mask = 1, lim = 0;
  int i = 0, j = 0;
  unsigned int state = ~0;

  if (m == 0) {
    return -1;
  }

  if (m > kWordLength) {
    printf("The length of substring should be <= machine's word length %d.",
           kWordLength);
    return 0;
  }
  // Init the mask table.
  for (i = 0; i < UCHAR_MAX; ++i) {
      b[i] = ~0;
  }
  for (i = m - 1, mask = 1; i >= 0 ; --i, mask <<= 1) {
    b[needle[i]] &= ~mask;
    lim |= mask;
  }
  lim = ~(lim >> 1);

  // Search the substring backward.
  for (j = n -1; j >= 0; --j) {
    state  = (state << 1) | b[haystack[j]];
    if (state < lim) {
      return j + 1;
    }
  }
  return -1;
}
