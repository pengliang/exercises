#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Coverts char between upper and lower case
 * according the program's name.
 */
int main(int argc, char *argv[]) {
  int c;

  if (strcmp(argv[0], "lower") == 0) {
    while ((c = getchar()) != EOF) {
      putchar(tolower(c));
    }
  } else {
    while ((c = getchar()) != EOF) {
      putchar(toupper(c));
    }
  }
  return 0;
}
