#include <stdio.h>
#include <stdlib.h>
#include "utils/get_line.h"

const int kMaxLineLength = 1000;

// Reverse the usr's input string.
//
// @param buffer, the buffer that store the usr's input
// @param str_length, the length of usr's input
void StringReverse(char *buffer, int str_length);

int main() {
  char *line_buf = malloc(sizeof(*line_buf) * kMaxLineLength);
  int line_length = 0;
  while(line_length = GetAllLine(&line_buf, kMaxLineLength)) {
    StringReverse(line_buf, line_length);
    fwrite(line_buf, line_length, sizeof(char), stdout);
  }
}

void StringReverse(char *buffer, int buf_length) {
  int i = buf_length - 1, j = 0;

  for (--i, j =0; j < i; ++j, --i) {
    char temp;
    temp = buffer[j];
    buffer[j] = buffer[i];
    buffer[i] = temp;
  }
}
