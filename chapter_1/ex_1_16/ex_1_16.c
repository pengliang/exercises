#include <stdio.h>

#define MAXLINE 1000  // maximum input line length

int my_getline(char line[], int length);
void copy(char from[], char to[]);

// print the length of arbitrary long input lines and as much as possible of
// the text, and print the longest input line at last.
int main() {
  int line_len = 0;  // current line length
  int max_len = 0;  // maximum length so far
  char line[MAXLINE];  // current input line
  char longest[MAXLINE]; // longest line saved here

  while ((line_len = my_getline(line,MAXLINE)) > 0) {
    printf("%d, %s", line_len, line);
    if (line_len > max_len) {
      max_len = line_len;
      copy(line, longest);
    }
  }
  if (max_len > 0) {
    printf("%s", longest);
  }
  return 0;
}

// getline: read a line and return its length
int my_getline(char line[], int length) {
  int current_char;
  int i = 0, j = 0;
  for (i = 0; (current_char = getchar()) != EOF && current_char != '\n'; ++i) {
    if (i < length - 2) {
      line[j] = current_char;
      ++j;
    }
  }
  if (current_char == '\n') {
    line[j] = current_char;
    ++j;
    ++i;
  }
  line[j] = '\0';
  return i;
}

// copy: copy 'from' string into 'to'; assume 'to' is big enough
void copy(char from[], char to[]) {
  int i = 0;
  while ((to[i] = from[i]) != '\0') {
    ++i;
  }
}
