#include <stdio.h>

// Verify that expression "getchar() != EOF" is 0 or 1.
int main() {
  int c;
  while (c = (getchar() != EOF)) {
    printf("%d\n", c);  // expect 1
  }
  // press Ctrl+D to reach this line, expect 0
  printf("%d - at EOF\n", c);
  return 0;
}

