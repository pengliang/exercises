#include <stdio.h>
#include <stdlib.h>

static const int kMaxLineLength = 1000;

// Remove trailing blanks and tabs, and delete blanks lines
int main() {
  char c;
  char *blank_buf = malloc(sizeof(*blank_buf) * kMaxLineLength);
  int buf_length = kMaxLineLength;
  int buf_index = 0;
  while ((c = getchar()) != EOF) {
    switch (c) {
      case ' ':
      case '\t':
        blank_buf[buf_index++] = c;
        break;
      case '\n':
        putchar(c);
        buf_index = 0;
        break;
      default:
        if (buf_index > 0) {
          fwrite(blank_buf, sizeof(*blank_buf), buf_index, stdout);
          buf_index = 0;
        }
        putchar(c);
    }
    if (buf_index == kMaxLineLength) {
      buf_length *= 2;
      blank_buf = realloc(blank_buf, buf_length * sizeof(*blank_buf));
    }
  }
  return 0;
}
