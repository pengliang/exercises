#include <stdio.h>
#include <string.h>
#include "utils/get_line.h"

const int kMaxLineLength = 1000;

// Prints the user's input in stdout.
//
// @param line_buf the buffer to store user's input.
// @param line_length the length of user's input, note that it is not the
//                    line_buf's length, but the actual length of user's input.
void PrintLine(char line_buf[], int line_length);

// Prints the length of arbitrary long input lines and as much as possible of
// the text, and print the longest input line at last.
int main() {
  // Current line length
  int line_len = 0;
  // Maximum length of user's input so far
  int max_len = 0;
  char line_buf[kMaxLineLength];
  char longest_line_buf[kMaxLineLength];

  while ((line_len = GetLine(line_buf, kMaxLineLength)) > 0) {
    printf("%d ", line_len);
    PrintLine(line_buf, line_len);
    if (line_len > max_len) {
      max_len = line_len;
      if (max_len > kMaxLineLength) {
        memcpy(longest_line_buf, line_buf, kMaxLineLength);
      } else {
        memcpy(longest_line_buf, line_buf, max_len);
      }
    }
  }
  if (max_len > 0) {
    printf("longest line: %d ", max_len);
    PrintLine(longest_line_buf, max_len);
   }
  return 0;
}

void PrintLine(char line_buf[], int line_length) {
   if (line_length > kMaxLineLength) {
      fwrite(line_buf, sizeof(char), kMaxLineLength, stdout);
    } else {
      fwrite(line_buf, sizeof(char), line_length, stdout);
    }
}
