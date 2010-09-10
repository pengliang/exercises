#include <stdio.h>

#define  MAXHIST  20  // max length of histogram
#define  MAXLEN  15  // max length of a word

// print a histogram of the lengths of words in input.
// this program print a horizontal version.

int main() {
  int current_char;
  int word_len = 0;  // length of a word
  int bar_len = 0;  // length of each bar
  int overflow = 0;  // number of words exceed the MAXLEN
  int state = 0;
  int word_lens[MAXLEN];
  int max_value = 0;  // maximum value of world_lens[]

  // Initialization of array word_lens[]
  for (int i = 0; i < MAXLEN; ++i) {
    word_lens[i] = 0;
  }
  // Statistical word length
  while ((current_char = getchar()) != EOF) {
    if (current_char == ' ' || current_char == '\n' || current_char == '\t') {
      state = 0;
      if (word_len > 0) {
        if (word_len < MAXLEN) {
          ++word_lens[word_len];
        } else {
          ++overflow;
        }
      }
      word_len = 0;
    } else if (state == 0) {
      state = 1;
      word_len = 1;
    } else {
      ++word_len;
    }
  }
  // Calculate the max value of array word_lens[]
  for (int i = 1; i < MAXLEN; ++i) {
    if (word_lens[i] > max_value) {
      max_value = word_lens[i];
    }
  }
  //  Print the histogram
  for (int i = 1; i < MAXLEN; ++i) {
    printf("%5d - %5d : ", i, word_lens[i]);
    if (word_lens[i] > 0) {
      if ((bar_len = word_lens[i] * MAXHIST / max_value) <= 0) {
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
  if (overflow > 0) {
    printf("%d words >= %d\n", overflow, MAXLEN);
  }
}
