#include <stdio.h>
#include <string.h>

static const int kMaxHistLength = 20;
static const int kMaxWordLength = 15;

enum ParserState {
  kStateOtherCharacters,
  kStateWhiteSpace
};

// Prints the horizontal histogram of the lengths of words in input.
//
// @param word_lens the array to store the number of words with length of
//                  1 2 3...(the array index +1)
// @param max_number_of_length the max value of the number of words with some
//                             length, also is the maximum value of word_lens.
// @param overflow number of the words that exceed the kMaxWordLength
static void PrintHorizontalHist(int word_lens[], int max_number_of_length,
                                int overflow);

// Print the vertical histogram of the lengths of words in input.
//
// @param word_lens the array to store the number of the words with length of
//                  1 2 3 ...(the array index + 1).
// @param max_number_of_length the max value of the number of words with some
//                             length, also is the maximum value of word_lens
// @param overflow number of the words that exceed the kMaxWordLength
static void PrintVerticalHist(int word_lens[], int max_number_of_length,
                              int overflow);

// Prints a histogram of the lengths of words in input.
int main() {
  int current_char;
  // Length of a word
  int word_len = 0;
  // Number of the words that exceed the kMaxWordLength
  int overflow = 0;
  // Maximum value of word_lens[]
  int max_number_of_length = 0;
  enum ParserState state = kStateOtherCharacters;
  int word_lens[kMaxWordLength];

  memset(word_lens, 0, sizeof(word_lens));

  // Statistics word length
  while ((current_char = getchar()) != EOF) {
    switch (state) {
      case kStateOtherCharacters:
        switch (current_char) {
          case ' ':
          case '\n':
          case '\t':
            state = kStateWhiteSpace;
            if (word_len > 0) {
              if (word_len < kMaxWordLength) {
                ++word_lens[word_len-1];
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
      default:
        break;
    }
  }
  for (int i = 0; i < kMaxWordLength; ++i) {
    if (word_lens[i] > max_number_of_length) {
      max_number_of_length = word_lens[i];
    }
  }
  PrintHorizontalHist(word_lens, max_number_of_length, overflow);
  PrintVerticalHist(word_lens, max_number_of_length, overflow);
}

static void PrintHorizontalHist(int word_lens[], int max_number_of_length,
                                int overflow) {
  // Length of each bar
  int bar_len = 0;

  for (int i = 0; i < kMaxWordLength; ++i) {
    printf("%5d - %5d : ", i + 1, word_lens[i]);
    if (word_lens[i] > 0) {
      bar_len = word_lens[i] * kMaxHistLength / max_number_of_length;
      if (bar_len == 0) {
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
    printf("%d words > %d\n", overflow, kMaxWordLength);
  }
}

static void PrintVerticalHist(int word_lens[], int max_number_of_length,
                              int overflow) {
  for (int i = kMaxHistLength; i > 0; --i) {
    for (int j = 0; j < kMaxWordLength; ++j) {
      if (word_lens[j] * kMaxHistLength / max_number_of_length >= i) {
        printf(" * ");
      } else {
        printf("   ");
      }
    }
    putchar('\n');
  }
  for (int i = 0; i < kMaxWordLength; ++i) {
    printf("%2d ", i + 1);
  }
  putchar('\n');
  for (int i = 0; i < kMaxWordLength; ++i) {
    printf("%2d ", word_lens[i]);
  }
  putchar('\n');
  if(overflow > 0) {
    printf("%d words > %d\n", overflow, kMaxWordLength);
  }
}
