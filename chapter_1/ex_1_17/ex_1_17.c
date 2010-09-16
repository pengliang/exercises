#include <stdio.h>
#include "../include/get_line.h"

const int kMaxLineLength = 1000;
const int kLengthThreshold = 80;

int main () {
  // Current line length
  int line_length;
  // Current line buffer
  char line_buf[kMaxLineLength];

  while ((line_length = GetLine(line_buf, kMaxLineLength)) > 0){
    if (line_length > kLengthThreshold) {
      if (line_length > kMaxLineLength) {
        fwrite(line_buf, kMaxLineLength, sizeof(char), stdout);
        putchar('\n');
      } else {
        fwrite(line_buf, line_length, sizeof(char), stdout);
      }
    }
  }
  return 0;
}

