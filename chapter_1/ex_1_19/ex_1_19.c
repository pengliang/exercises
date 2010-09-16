#include <stdio.h>
#include "../include/get_line.h"

const int kMaxLineLength = 1000;

void StringReverse(char buffer[], int buf_length);

int main() {
  char line_buffer[kMaxLineLength];
  int line_length = 0;
  while(line_length = GetLine(line_buffer, kMaxLineLength)) {
    StringReverse(line_buffer, kMaxLineLength);
    fwrite(line_buffer, line_length, sizeof(char), stdout);
  }
}

void StringReverse(char buffer[], int buf_length) {
  int i = 0, j = 0;
  char temp;

  for (i = 0; buffer[i] != '\0' && buffer[i] != '\n' && i < buf_length; ++i) {}
  for (--i, j =0; j < i; ++j, --i) {
    temp = buffer[j];
    buffer[j] = buffer[i];
    buffer[i] = temp;
  }
}
