#include <stdio.h>
#include <ctype.h>
#include <string.h>

static const int kMaxHistLength = 15;
static const int kMaxCharNum = 255;

// Prints a histogram of the frequencies of different characters in input
int main() {
  int current_char;
  // Length of each bar
  int bar_len = 0;
  // Maximum value of the number of chars
  int max_value = 0;
  // Character counters;
  int char_count[kMaxCharNum];

  memset(char_count, 0, sizeof(char_count));

  while ((current_char = getchar()) != EOF) {
    if (current_char < kMaxCharNum) {
      ++char_count[current_char];
    }
  }
  for (int i = 0; i < kMaxCharNum; ++i) {
    if (char_count[i] > max_value) {
      max_value = char_count[i];
    }
  }
  // Prints histogram
  for (int i = 0; i < kMaxCharNum; ++i) {
    if (isprint(i)) {
      printf("%3d  - %c  - %3d : ", i, i, char_count[i]);
    } else {
      printf("%3d  -    - %3d : ", i, char_count[i]);
    }
    if (char_count[i] > 0) {
      if ((bar_len = char_count[i] * kMaxHistLength / max_value) == 0) {
        bar_len = 1;
      }
    } else {
      bar_len = 0;
    }
    for (int j = 0; j < bar_len; ++j) {
      putchar('*');
    }
    putchar('\n');
  }
  return 0;
}
