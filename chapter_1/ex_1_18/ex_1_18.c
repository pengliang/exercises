#include <stdio.h>
#include "../include/get_line.h"

const int kMaxLineLength = 1000;

// Remove the trailing blanks and tabs from each line of input and delete
// entirely blank lines.
//
// @param buffer the buffer to store string, note that maybe no '\0' end
// @param buf_length the length of buffer.
int RemoveTrailingBlanks(char buffer[], int buf_length);

// Remove trailing blanks and tabs, and delete blanks lines
int main() {
  char line_buf[kMaxLineLength];
  int line_length = 0;

  while (GetLine(line_buf, kMaxLineLength) > 0) {
    if((line_length = RemoveTrailingBlanks(line_buf, kMaxLineLength)) > 0) {
      fwrite(line_buf, line_length, sizeof(char), stdout);
    }
  }
  return 0;
}

int RemoveTrailingBlanks(char buffer[], int buf_length) {
  int i = 0;
  int line_break = 0;
  while (buffer[i] != '\0' && buffer[i] != '\n' && i < buf_length) {
    ++i;
  }
  if (buffer[i] == '\n') {
    line_break = 1;
  }
  for (--i; i >= 0 && (buffer[i] == ' ' || buffer[i] == '\t'); --i) {}
  if (line_break) {
    buffer[++i] = '\n';
  }
  if (i >= 0 && i < buf_length - 1) {
    buffer[++i] = '\0';
  }
  return i;
}
