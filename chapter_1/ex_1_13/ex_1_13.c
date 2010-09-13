#include <stdio.h>
#include <string.h>

#define MAX_HIST_LENGTH 20
#define MAX_WORD_LENGTH 15

enum ParserState {
  kStateOtherCharacters,
  kStateWhiteSpace
};

void PrintHorizontalHist(int word_lens[], int max_value, int overflow);
void PrintVerticalHist(int word_lens[], int max_value, int overflow);

// prints a histogram of the lengths of words in input.
int main() {
  int current_char;
  // Length of a word
  int word_len = 0;
  // Number of words exceeds the MAX_WORD_LENGTH
  int overflow = 0;
  // Maximum value of world_lens[]
  int max_value = 0;
  enum ParserState state = kStateOtherCharacters;
  int word_lens[MAX_WORD_LENGTH];

  memset(word_lens, 0, sizeof(word_lens));

  // statistics  word length
  while ((current_char = getchar()) != EOF) {
    switch (state) {
      case kStateOtherCharacters:
        switch (current_char) {
          case ' ':
          case '\n':
          case '\t':
            state = kStateWhiteSpace;
            if (word_len > 0) {
              if (word_len < MAX_WORD_LENGTH) {
                ++word_lens[word_len];
              } else {
                ++overflow;
              }
            }
            word_len = 0;
            break;
          default:
            ++word_len;
        }
        break;
     case kStateWhiteSpace:
        switch (current_char) {
          case ' ':
          case '\n':
          case '\t':
            break;
          default:
            state = kStateOtherCharacters;
            word_len = 1;
        }
        break;
     default: {}
    }
  }
  for (int i = 1; i < MAX_WORD_LENGTH; ++i) {
    if (word_lens[i] > max_value) {
      max_value = word_lens[i];
    }
  }
  PrintHorizontalHist(word_lens, max_value, overflow);
  PrintVerticalHist(word_lens, max_value, overflow);
}

void PrintHorizontalHist(int word_lens[], int max_value, int overflow) {
  // Length of each bar
  int bar_len = 0;

  for (int i = 1; i < MAX_WORD_LENGTH; ++i) {
    printf("%5d - %5d : ", i, word_lens[i]);
    if (word_lens[i] > 0) {
      if ((bar_len = word_lens[i] * MAX_HIST_LENGTH / max_value) <= 0) {
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
  if (overflow > 0) {
    printf("%d words >= %d\n", overflow, MAX_WORD_LENGTH);
  }
}

void PrintVerticalHist(int word_lens[], int max_value, int overflow) {
  for (int i = MAX_HIST_LENGTH; i > 0; --i) {
    for (int j = 1; j < MAX_WORD_LENGTH; ++j) {
      if (word_lens[j] * MAX_HIST_LENGTH / max_value >= i) {
        printf(" * ");
      } else {
        printf("   ");
      }
    }
    putchar('\n');
  }
  for (int i = 1; i < MAX_WORD_LENGTH; ++i) {
    printf("%2d ", i);
  }
  putchar('\n');
  for (int i = 1; i < MAX_WORD_LENGTH; ++i) {
    printf("%2d ", word_lens[i]);
  }
  putchar('\n');
  if(overflow > 0) {
    printf("%d words >= %d\n", overflow, MAX_WORD_LENGTH);
  }
}
