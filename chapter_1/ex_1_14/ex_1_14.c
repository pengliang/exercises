#include <stdio.h>
#include <ctype.h>

#define MAXHIST 15  // max length of histogram
#define MAXCHAR 128  // max different characters

// print a histogram of the frequencies of different characters in input
int main() {
  int current_char;
  int bar_len = 0;  // length of each bar
  int max_value = 0;  // maximum value of the number of chars
  int char_count[MAXCHAR]; // character counters;

  // Array initialization
  for (int i = 0; i < MAXCHAR; ++i) {
    char_count[i] = 0;
  }
  while ((current_char = getchar()) != EOF) {
    if (current_char < MAXCHAR) {
      ++char_count[current_char];
    }
  }
  // Calculate the max_value
  for (int i = 0; i < MAXCHAR; ++i) {
    if (char_count[i] > max_value) {
      max_value = char_count[i];
    }
  }
  // Print the histogram
  for (int i = 1; i < MAXCHAR; ++i) {
    if (isprint(i)) {
      printf("%3d  - %c  - %3d : ", i, i, char_count[i]);
    } else {
      printf("%3d  -    - %3d : ", i, char_count[i]);
    }
    if (char_count[i] > 0) {
      if ((bar_len = char_count[i] * MAXHIST / max_value) <= 0) {
        bar_len = 1;
      }
    } else {
      bar_len = 0;
    }
    while (bar_len > 0) {
      putchar('*');
      --bar_len;
    }
    putchar('\n');
  }
  return 0;
}
