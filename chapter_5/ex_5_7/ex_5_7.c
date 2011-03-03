#include <stdio.h>
#include <string.h>
#include "utils/get_line.h"

// Maximum length of one line
static const int kMaxLen = 1000;
// Size of available storage space
static const int kMaxStore = 5000;

/* Reads input lines
 *
 * @param lines_ptr array to store lines storage address
 * @param lines_store address to store the lines
 * @param max_lines maximum number of lines will be read
 * @return the number of lines read from input
 *         -1 for the buffer overflow.
 */
int ReadLimitedLines(char *lines_ptr[], char *lines_store, int max_lines) {
  int len, nlines = 0;
  // Temp array for one line
  char line_buf[kMaxLen];
  // Address of next line to store
  char *p = lines_store;
  char *lines_stop = lines_store + kMaxStore;

  while ((len = GetLimitedLine(line_buf, kMaxLen)) > 0) {
    if (len >= kMaxLen) {
      len = kMaxLen;
    }
    if (nlines >= max_lines || p + len > lines_stop) {
      return -1;
    } else {
      line_buf[len - 1] = '\0';
      strcpy(p, line_buf);
      lines_ptr[nlines++] = p;
      p += len;
    }
  }
  return nlines;
}
