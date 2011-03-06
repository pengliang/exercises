#include "get_line.h"
#include <string.h>
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

int GetLines(char *line_ptr[], int max_lines) {
  int temp_buf_len = 100;
  char *line_buf = malloc(sizeof(char) * temp_buf_len);
  int len = 0, nlines = 0;
  char *p;

  while ((len = GetLine(&line_buf, 100)) > 0) {
    if (nlines > max_lines) {
      return -1;
    }
    if ((p = malloc(sizeof(char) * len)) == NULL) {
      return -2;
    }
    memcpy(p, line_buf, len);
    line_ptr[nlines++] = p;
  }
  return nlines;
}
