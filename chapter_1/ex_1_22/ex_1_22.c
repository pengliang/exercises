#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Maximum column of output
const int kMaxCol = 10;
const int kTabSize = 8;

// Fold long input lines into multiple shorter lines
int main() {
  // Current input char
  int c;
  // Position in the line, start from 0
  int pos = 0;

  // Output line buffer
  char *line = malloc(sizeof(*line) * kMaxCol);
  memset(line, '\0', kMaxCol);

  while ((c = getchar()) != EOF) {
    line[pos] = c;
    switch (c) {
      case '\t':
        // Expand tab into blanks, at least one blank.
        line[pos] = ' ';
        for (++pos; pos < kMaxCol && pos % kTabSize != 0; ++pos) {
          line[pos] = ' ';
        }
        if (pos == kMaxCol) {
          fwrite(line, sizeof(*line), kMaxCol, stdout);
          putchar('\n');
          pos = 0;
        }
        break;
      case '\n':
        if (pos > 0) {
          fwrite(line, sizeof(*line), pos, stdout);
          putchar('\n');
          pos = 0;
        }
        break;
      default:
        if (++pos == kMaxCol) {
          //Find the last blank's position
          while (pos > 0 && line[--pos] != ' ') {}
          if (pos == 0) {
            // No blank in this line, output all.
            fwrite(line, sizeof(*line), kMaxCol, stdout);
          } else {
            // At least on blank found
            fwrite(line, sizeof(*line), ++pos, stdout);
          }
          putchar('\n');
          if (pos > 0 && pos < kMaxCol) {
            memmove(line, line + pos, kMaxCol - pos);
            pos = kMaxCol - pos;
          } else {
            pos = 0;
          }
        }
    }
  }
  return 0;
}
