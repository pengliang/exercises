#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int Getline(char line_buffer[], int length);
void Copy(char from[], char to[]);

// prints the length of arbitrary long input lines and as much as possible of
// the text, and print the longest input line at last.
int main() {
  // Current line length
  int line_len = 0;
  // Maximum length so far
  int max_len = 0;
  char line_buf[MAX_LINE_LENGTH];
  char longest_line_buf[MAX_LINE_LENGTH];

  while ((line_len = Getline(line_buf,MAX_LINE_LENGTH)) > 0) {
    printf("%d, %s", line_len, line_buf);
    if (line_len > max_len) {
      max_len = line_len;
      Copy(line_buf, longest_line_buf);
    }
  }
  if (max_len > 0) {
    printf("%s", longest_line_buf);
  }
  return 0;
}

int Getline(char line_buf[], int length) {
  int current_char;
  int i = 0, j = 0;
  for (i = 0; (current_char = getchar()) != EOF && current_char != '\n'; ++i) {
    if (i < length - 2) {
      line_buf[j] = current_char;
      ++j;
    }
  }
  if (current_char == '\n') {
    line_buf[j] = current_char;
    ++j;
    ++i;
  }
  line_buf[j] = '\0';
  return i;
}

void Copy(char from[], char to[]) {
  int i = 0;
  while ((to[i] = from[i]) != '\0') {
    ++i;
  }
}
