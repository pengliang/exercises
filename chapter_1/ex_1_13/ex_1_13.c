#include <stdio.h>

#define  MAXHIST  20  // max length of histogram
#define  MAXLEN  15  // max length of a word

void print_horizontal_hist(int word_lens[], int max_value, int overflow);
void print_vertical_hist(int word_lens[], int max_value, int overflow);

// print a histogram of the lengths of words in input.
int main() {
  int current_char;
  int word_len = 0;  // length of a word
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
  print_horizontal_hist(word_lens, max_value, overflow);
  print_vertical_hist(word_lens, max_value, overflow);
}
//  Print the horizontal histogram
void print_horizontal_hist(int word_lens[], int max_value, int overflow) {
  int bar_len = 0;  // length of each bar
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
// Print the vertical histogram
void print_vertical_hist(int word_lens[], int max_value, int overflow) {
  for (int i = MAXHIST; i > 0; --i) {
    for (int j = 1; j < MAXLEN; ++j) {
      if (word_lens[j] * MAXHIST / max_value >= i) {
        printf(" * ");
      } else {
        printf("   ");
      }
    }
    putchar('\n');
  }
  for (int i = 1; i < MAXLEN; ++i) {
    printf("%2d ", i);
  }
  putchar('\n');
  for (int i = 1; i < MAXLEN; ++i) {
    printf("%2d ", word_lens[i]);
  }
  putchar('\n');
  if(overflow > 0) {
    printf("%d words >= %d\n", overflow, MAXLEN);
  }
}
