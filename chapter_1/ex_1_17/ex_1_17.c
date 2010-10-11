#include <stdio.h>
#include <stdlib.h>
#include "utils/get_line.h"

const int kMaxLineLength = 10;
const int kLengthThreshold = 3;

int main () {
  // Current line length
  int line_length = 0;
  // Current line buffer
  char *line_buf = malloc(sizeof(char) * kMaxLineLength);
  while ((line_length = GetAllLine(&line_buf, kMaxLineLength)) > 0){
    if (line_length > kLengthThreshold) {
      fwrite(line_buf, line_length, sizeof(char), stdout);
    }
  }
  return 0;
}

