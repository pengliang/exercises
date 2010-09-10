#include <stdio.h>

// escape tabs and backspaces with visible characters
int main() {
  int current_char;

  while ((current_char = getchar()) != EOF) {
    switch (current_char) {
      case '\t': {
        printf("\\t");
        break;
      }
      case '\b': {
        printf("\\b");
        break;
      }
      case '\\': {
        printf("\\\\");
        break;
      }
      default: {
        putchar(current_char);
      }
    }
  }
  return 0;
}
