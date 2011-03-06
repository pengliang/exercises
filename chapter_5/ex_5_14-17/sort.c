#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// max length of the field
static const int kMaxFieldLen = 100;

/* Calculates the length of the string s,
 * not including the terminating '\0' character.
 *
 * @param s string
 * @return the lenght of string s
 */
static int strlen(const char *s) {
  int i = 0;
  while (*s++ != '\0') {
    ++i;
  }
  return i;
}

/* Copys the substring from string str to substr.
 * The substring's length must be less than max_sub_len
 * and its position is specified by begin and end.
 *
 * @param substr[out] buffer to store the substring
 * @param str source string buffer
 * @param max_sub_len the max size of substr buffer
 * @param begin substring's start position
 * @param end substring's end position
 * @return the substring buffer's address
 */
static char *substring(char *substr,
                       const char *str,
                       int max_sub_len,
                       int begin,
                       int end) {
  int i = 0, j = 0;
  int len = 0;

  if (begin < 0 || end < 0 || begin > end) {
    printf("Error: wrong field parameter.");
    exit(1);
  }

  len = strlen(str);
  if (end > len) {
    end = len;
  }

  if (end - begin > max_sub_len) {
    end = begin + max_sub_len;
  }
  for (i = begin, j = 0; i < end; ++i, ++j) {
    substr[j] = str[i];
  }
  substr[j] = '\0';
  return substr;
}

/* Compares two strings by numerical order.
 *
 * @param s1 string
 * @param s2 string
 * @return an integer less than, equal to, or greater than zero
 *         if s1 is found, respectively, to be less than, to match,
 *         or be greater than s2 by numerical order.
 */
static int numcmp(const char *s1, const char *s2) {
  double v1, v2;
  extern int field_begin, field_end;

  if (option & kField) {
    char substr1[kMaxFieldLen], substr2[kMaxFieldLen];
    v1 = atof(substring(substr1, s1, kMaxFieldLen, field_begin, field_end));
    v2 = atof(substring(substr2, s2, kMaxFieldLen, field_begin, field_end));
  } else {
    v1 = atof(s1);
    v2 = atof(s2);
  }
  return v1 - v2;
}

/* Compare two strings.
 * The rules are specified by global var option.
 *
 * @param s1 string
 * @param s2 string
 * @return an integer less than, equal to, or greater than zero
 *         if s1 is found, respectively, to be less than, to match,
 *         or be greater than s2 according to the rule.
 */
static int strcmp(const char *s1, const char *s2) {
  extern field_begin, field_end;
  int end;
  int i = 0, j = 0;
  int len1, len2;
  char a, b;
  len1 = strlen(s1);
  len2 = strlen(s2);

  if (option & kField) {
    i = j = field_begin;
    if (field_end > len1 || field_end > len2) {
      end = len1 >= len2 ? len2 : len1;
    } else {
      end = field_end;
    }
  } else {
    i = j = 0;
    end = len1 >= len2 ? len2 : len1;
  }

  do {
    if (option & kDir) {
      while (i < end && !isalnum(s1[i]) && s1[i] != ' ' && s1[i] != '\0') {
        ++i;
      }
      while (j < end && !isalnum(s2[j]) && s2[j] != ' ' && s2[j] != '\0') {
        ++j;
      }
    }

    a = option & kCase ? tolower(s1[i]) : s1[i];
    b = option & kCase ? tolower(s2[j]) : s2[j];
    ++i;
    ++j;
  } while (a == b && i < end && j < end);

  return s1[i] - s2[j];
}

/* Swaps two elements in the array
 *
 * @param v pointer array
 * @param i first elements index in array
 * @param j second elements index
 */
void swap(void *v[], int i, int j) {
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* Sorts an array's elements between left and right index.
 * The base argument points to the start of the array.
 * The contents of the array are sorted in ascending order
 * according to a comparison function pointed to by comp, which is
 * called with two arguments that point to the objects being compared.
 *
 * @param base point to the start of the array.
 * @param left start index of the array to be sorted.
 * @param right end index of the array to be sorted.
 * @param comp comarison function which must return an integer less than,
 *             equal to, or greater than zero if the first argument is
 *             considered to be respectively less than, equal to,
 *             or greater than the second. If two members compare as equal,
 *             their order in the sorted array is undefined.
 */
static void QuickSort(void *base[], int left, int right,
               int (*comp)(void *, void *)) {
  int i, last;

  if (left >= right) {
    return;
  }

  swap(base, left, (left + right) / 2);

  last = left;

  for (i = left + 1; i <= right; ++i) {
    if ((*comp)(base[i], base[left]) < 0) {
      swap(base, ++last, i);
    }
  }
  swap(base, left, last);

  QuickSort(base, left, last - 1, comp);
  QuickSort(base, last + 1, right, comp);
}

void SortLines(char *line_ptr[], int nlines) {
  extern char option;

  QuickSort((void **) line_ptr, 0, nlines - 1,
            (int (*)(void *, void *)) (option & kNumeric ? numcmp : strcmp));
}
