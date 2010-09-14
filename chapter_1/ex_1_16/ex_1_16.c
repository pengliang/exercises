#include <stdio.h>
#include <string.h>

const int MAX_LINE_LENGTH = 1000;

// Reads a line from the standard input. If the user's input is ended with
// line-feed '\n', the line feed character is also included in the output.
//
// @param line_buffer the buffer to store the user's input
// @param length the maximum length of the buffer
// @return the length of the user's input
int Getline(char line_buffer[], int length);

// Prints the length of arbitrary long input lines and as much as possible of
// the text, and print the longest input line at last.
int main() {
  // Current line length
  int line_len = 0;
  // Maximum length so far
  int max_len = 0;
  char line_buf[MAX_LINE_LENGTH];
  char longest_line_buf[MAX_LINE_LENGTH];

  while ((line_len = Getline(line_buf,MAX_LINE_LENGTH)) > 0) {
    printf("%d ", line_len);
    if(line_len > MAX_LINE_LENGTH) {
      fwrite(line_buf, MAX_LINE_LENGTH, sizeof(char), stdout);
      putchar('\n');
    } else {
      fwrite(line_buf, line_len, sizeof(char), stdout);
    }
    if (line_len > max_len) {
      max_len = line_len;
      if (max_len > MAX_LINE_LENGTH) {
        memcpy(longest_line_buf, line_buf, MAX_LINE_LENGTH);
      } else {
        memcpy(longest_line_buf, line_buf, max_len);
      }
    }
  }
  if (max_len > 0) {
    printf("longest line: %d ", max_len);
    if (max_len > MAX_LINE_LENGTH) {
      fwrite(longest_line_buf, MAX_LINE_LENGTH, sizeof(char), stdout);
      putchar('\n');
    } else {
      fwrite(longest_line_buf, max_len, sizeof(char), stdout);
    }
  }
  return 0;
}

int Getline(char line_buf[], int length) {
  int current_char;
  int i = 0, j = 0;
  for (i = 0; (current_char = getchar()) != EOF && current_char != '\n'; ++i) {
    if (i < length) {
      line_buf[j] = current_char;
      ++j;
    }
  }
  if (j < length - 1 && current_char == '\n') {
    line_buf[j] = current_char;
    ++j;
    ++i;
  }
  if (j < length - 1) {
    line_buf[j] = '\0';
  }
  return i;
}
