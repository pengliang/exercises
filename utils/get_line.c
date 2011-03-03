#include "get_line.h"
#include <stdio.h>
#include <stdlib.h>

int GetLimitedLine(char *line_buf, int line_buf_length) {
  int current_char;
  int line_length = 0, buf_index = 0;
  for (line_length = 0; (current_char = getchar()) != EOF
      && current_char != '\n'; ++line_length) {
    if (line_length < line_buf_length) {
      line_buf[buf_index] = current_char;
      ++buf_index;
    }
  }
  if (line_length < line_buf_length - 1 && current_char == '\n') {
    line_buf[buf_index] = current_char;
    ++buf_index;
    ++line_length;
  }
  if (line_length < line_buf_length - 1) {
    line_buf[buf_index] = '\0';
  }
  return line_length;
}

int GetLine(char **line_buf, int line_buf_length) {
  int current_char;
  int line_length = 0, buf_index = 0;
  for (line_length = 0; (current_char = getchar()) != EOF
      && current_char != '\n'; ++line_length) {
    if (line_length < line_buf_length) {
      *((*line_buf) + buf_index) = current_char;
      ++buf_index;
    } else {
      line_buf_length *= 2;
      *line_buf = realloc(*line_buf, line_buf_length * sizeof(*line_buf));
      *((*line_buf) + buf_index) = current_char;
      ++buf_index;
    }
  }
  if (line_length > line_buf_length - 2) {
    line_buf_length += 2;
    *line_buf = realloc(*line_buf, line_buf_length * sizeof(*line_buf));
  }
  if (current_char == '\n') {
    *((*line_buf) + buf_index) = current_char;
    ++buf_index;
    ++line_length;
  } else {
    *line_buf[buf_index] = '\0';
  }
  return line_length;
}
