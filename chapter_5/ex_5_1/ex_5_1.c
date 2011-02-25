#include <stdio.h>
#include <ctype.h>

enum PaserState {
  kStart,
  kSign,
  kInteger,
};

/* Gets the next integer from input into *pn
 *
 * @param pn pointer to store the integer read from input.
 * @return 0 for input is not a number
 *         1 for a number is read correctly.
 */
int GetInt(int *pn) {
  char c, sign_c;
  enum PaserState state = kStart;
  int sign = 1;
  *pn  = 0;

  while ((c = getchar()) != EOF) {
    switch (state) {
      case kStart:
        if (isdigit(c)) {
          state = kInteger;
          *pn = 10 * (*pn) + (c - '0');
        } else {
          switch (c) {
            case ' ':
            case '\t':
            case '\n':
              break;
            case '-':
            case '+':
              sign = (c == '-') ? -1 : 1;
              sign_c = c;
              state = kSign;
              break;
            default:
              return 0;
          }
        }
        break;
      case kSign:
        if (isdigit(c)) {
          *pn = 10 * (*pn) + (c - '0');
          state = kInteger;
        } else {
          ungetc(c, stdin);
          ungetc(sign_c, stdin);
          return 0;
        }
        break;
      case kInteger:
        if (isdigit(c)) {
          *pn = 10 * (*pn) + (c - '0');
        } else {
          *pn *= sign;
          if (c != '\n') {
            ungetc(c, stdin);
          }
          return 1;
        }
        break;
    }
  }
  return 1;
}

int main() {
  int pn;
  while (GetInt(&pn)) {
    printf("%d\t", pn);
  }
}
