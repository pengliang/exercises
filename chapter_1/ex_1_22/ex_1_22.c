#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Maximum column of output
static const int kMaxCol = 10;
static const int kTabSize = 8;

enum PaserState {
  kStart,
  kNormalCode,
  kLeadingBlank,
  kTrailingBlank
};

// Fold long input lines into multiple shorter lines after the last non-blank
// character occurs before the n-th column of input.
int main() {
  // Current input char
  int c;
  // Position in the line, start from 0
  int pos = 0;
  int trailing_spaces = 0;
  int trailing_tabs = 0;
  enum PaserState state = kStart;

  while ((c = getchar()) != EOF) {
    switch (state) {
      case kStart:
        switch (c) {
          case ' ':
          case '\t':
            // Leading blanks doesn't count for columns.
            state = kLeadingBlank;
            break;
          case '\n':
            pos = 0;
            break;
          default:
            state = kNormalCode;
            putchar(c);
            ++pos;
            break;
        }
        break;
      case kLeadingBlank:
        switch (c) {
          case ' ':
          case '\t':
            break;
          case '\n':
            putchar(c);
            pos = 0;
            state = kStart;
          default:
            state = kNormalCode;
            putchar(c);
            ++pos;
        }
        break;
      case kNormalCode:
        trailing_spaces = 0;
        trailing_tabs = 0;
        switch (c) {
          case ' ':
            ++pos;
            state = kTrailingBlank;
            ++trailing_spaces;
            break;
          case '\t':
            pos += kTabSize - pos % kTabSize;
            state = kTrailingBlank;
            ++trailing_tabs;
            break;
          case '\n':
            pos = 0;
            state = kStart;
            putchar(c);
            break;
          default:
            if (pos >= kMaxCol) {
              putchar('\n');
              putchar(c);
              pos = 1;
            } else if (++pos == kMaxCol) {
              putchar(c);
              putchar('\n');
              pos = 0;
              state = kStart;
            } else {
              putchar(c);
            }
            break;
        }
        break;
      case kTrailingBlank:
        switch (c) {
          case ' ':
            ++pos;
            ++trailing_spaces;
            break;
          case '\t':
            pos += kTabSize - pos % kTabSize;
            ++trailing_tabs;
            break;
          case '\n':
            putchar(c);
            pos = 0;
            state = kStart;
            break;
          default:
            if (pos >= kMaxCol) {
              putchar('\n');
              putchar(c);
              pos = 1;
              state = kNormalCode;
            } else if (++pos == kMaxCol) {
              putchar(c);
              putchar('\n');
              pos = 0;
              state = kStart;
            } else {
              while (trailing_spaces--) {
                putchar(' ');
              }
              while (trailing_tabs--) {
                putchar('\t');
              }
              putchar(c);
              state = kNormalCode;
            }
        }
        break;
    }
  }
 return 0;
}
