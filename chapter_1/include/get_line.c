#include <stdio.h>
#include "get_line.h"

int GetLine(char line_buf[], int line_buf_length) {
  int current_char;
  int line_length = 0, buf_index = 0;
  for (line_length = 0; (current_char = getchar()) != EOF && current_char != '\n'; ++line_length) {
    if (line_length < line_buf_length) {
      line_buf[buf_index] = current_char;
      ++buf_index;
    }
  }
  if (buf_index < line_buf_length - 1 && current_char == '\n') {
    line_buf[buf_index] = current_char;
    ++buf_index;
    ++line_length;
  }
  if (buf_index < line_buf_length - 1) {
    line_buf[buf_index] = '\0';
  }
  return line_length;
}

