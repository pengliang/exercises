#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Maximum column of output
static const int kMaxCol = 10;
static const int kTabSize = 8;

enum PaserState {
  kNewLine,
  // After folding, the new line may be starting with blank.
  kLeadingBlank,
  // Each blank may be the break position.
  kTrailingBlank,
  // May be new line after trailing blank.
  kMayBeNewLine
};

// Fold long input lines into multiple shorter lines after the last non-blank
// character occurs before the n-th column of input.
int main() {
  // Current input char
  int c;
  // Position in the line, start from 0
  int pos = 0;
  enum PaserState state = kNewLine;

  // Buffer for blanks which may be at break position.
  char blank_buf[kMaxCol];
  // Buffer for the non blank contents after the maybe break position.
  char new_line_buf[kMaxCol];
  // Index for the buffers above.
  int b_i = 0, n_i = 0;

  while ((c = getchar()) != EOF) {
    switch (state) {
      case kNewLine:
        switch (c) {
          case ' ':
            ++pos;
            blank_buf[b_i++] = c;
            state = kTrailingBlank;
            break;
          case '\t':
            pos += kTabSize - pos % kTabSize;
            blank_buf[b_i++] = c;
            state = kTrailingBlank;
            break;
          case '\n':
            pos = 0;
            b_i = 0;
            n_i = 0;
            putchar(c);
            break;
          default:
            if (pos >= kMaxCol) {
              putchar('\n');
              pos = 0;
              n_i = 0;
              b_i = 0;
            }
            ++pos;
            putchar(c);
        }
        break;
      case kTrailingBlank:
        switch (c) {
          case ' ':
            if (pos >= kMaxCol) {
              putchar('\n');
              pos = 0;
              b_i = 0;
              state = kLeadingBlank;
            } else {
              blank_buf[b_i++] = c;
              ++pos;
            }
            break;
          case '\t':
            if (pos >= kMaxCol) {
              putchar('\n');
              pos = 0;
              b_i = 0;
              state = kLeadingBlank;
            } else {
              blank_buf[b_i++] = c;
              pos += kTabSize - pos % kTabSize;
            }
            break;
          case '\n':
            // Forget the cached trailing blanks.
            b_i = 0;
            // New line.
            putchar(c);
            pos = 0;
            state = kNewLine;
            break;
          default:
            if (pos >= kMaxCol) {
              putchar('\n');
              pos = 0;
              b_i = 0;
              ++pos;
              putchar(c);
              state = kNewLine;
            } else {
              ++pos;
              new_line_buf[n_i++] = c;
              state = kMayBeNewLine;
            }
        }
        break;
      case kLeadingBlank:
        switch (c) {
          // Skip the leading blank for newline.
          case ' ':
          case '\t':
            break;
          default:
            putchar(c);
            ++pos;
            state = kNewLine;
        }
        break;
      case kMayBeNewLine:
        switch (c) {
          case ' ':
            fwrite(blank_buf, sizeof(char), b_i, stdout);
            b_i = 0;
            fwrite(new_line_buf, sizeof(char), n_i, stdout);
            n_i = 0;
            ++pos;
            blank_buf[b_i++] = c;
            state = kTrailingBlank;
            break;
          case '\t':
            fwrite(blank_buf, sizeof(char), b_i, stdout);
            b_i = 0;
            fwrite(new_line_buf, sizeof(char), n_i, stdout);
            n_i = 0;
            pos += kTabSize - pos % kTabSize;
            blank_buf[b_i++] = c;
            state = kTrailingBlank;
            break;
          case '\n':
            fwrite(blank_buf, sizeof(char), b_i, stdout);
            b_i = 0;
            fwrite(new_line_buf, sizeof(char), n_i, stdout);
            n_i = 0;
            putchar(c);
            pos = 0;
            state = kNewLine;
            break;
          default:
            if (pos >= kMaxCol) {
              // New line
              putchar('\n');
              pos = 0;
              // Flush the cached new line contents.
              fwrite(new_line_buf, sizeof(char), n_i, stdout);
              pos = n_i;
              n_i = 0;
              // Forget the cached blank;
              b_i = 0;
              putchar(c);
              ++pos;
              state = kNewLine;
            } else {
              ++pos;
              new_line_buf[n_i++] = c;
            }
            break;
        }
        break;
    }
  }
 return 0;
}
