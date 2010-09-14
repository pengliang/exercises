#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int MAX_HIST_LENGTH = 15;
const int MAX_CHAR_NUM = 255;

// Prints a histogram of the frequencies of different characters in input
int main() {
  int current_char;
  // Length of each bar
  int bar_len = 0;
  // Maximum value of the number of chars
  int max_value = 0;
  // Character counters;
  int char_count[MAX_CHAR_NUM];

  memset(char_count, 0, sizeof(char_count));

  while ((current_char = getchar()) != EOF) {
    if (current_char < MAX_CHAR_NUM) {
      ++char_count[current_char];
    }
  }
  for (int i = 0; i < MAX_CHAR_NUM; ++i) {
    if (char_count[i] > max_value) {
      max_value = char_count[i];
    }
  }
  // Prints histogram
  for (int i = 0; i < MAX_CHAR_NUM; ++i) {
    if (isprint(i)) {
      printf("%3d  - %c  - %3d : ", i, i, char_count[i]);
    } else {
      printf("%3d  -    - %3d : ", i, char_count[i]);
    }
    if (char_count[i] > 0) {
      if ((bar_len = char_count[i] * MAX_HIST_LENGTH / max_value) == 0) {
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
