#include "getopt.h"
#include <stdio.h>

// Signal that a number was found
static const int kNumber = '0';
static const int kFunc = 'f';

enum PaserState {
  kStart,
  kFunction,
  kOperandInteger,
  kOperandFraction,
  kMinus,
  kPlus
};

/* Gets the next operator or numeric operand */
int GetOpt(char op[]) {
  char c;
  enum PaserState state = kStart;
  int i  = 0;

  while ((c = getchar()) != EOF) {
    switch (state) {
      case kStart:
        i = 0;
        if (isdigit(c)) {
          state = kOperandInteger;
          op[i++] = c;
        } else if (islower(c)) {
          op[i++] = c;
          state = kFunction;
        } else {
          switch (c) {
            case ' ':
            case '\t':
              break;
            case '-':
              state = kMinus;
              break;
            case '+':
              state = kPlus;
              break;
            default:
              return c;
          }
        }
        break;
      case kFunction:
        if (islower(c)) {
          op[i++] = c;
        } else {
          op[i] = '\0';
          ungetc(c, stdin);
          if (i > 1) {
            return kFunc;
          } else {
            return op[i-1];
          }
        }
        break;
      case kMinus:
        if (isdigit(c)) {
          op[i++] = '-';
          op[i++] = c;
          state = kOperandInteger;
        } else {
          ungetc(c, stdin);
          return '-';
        }
        break;
      case kPlus:
        if (isdigit(c)) {
          op[i++] = '+';
          op[i++] = c;
          state = kOperandInteger;
        } else {
          ungetc(c, stdin);
          return '+';
        }
        break;
      case kOperandInteger:
        if (isdigit(c)) {
          op[i++] = c;
        } else {
          switch (c) {
            case '.':
              op[i++] = '.';
              state = kOperandFraction;
              break;
            default:
              op[i] = '\0';
              ungetc(c, stdin);
              return kNumber;
          }
        }
        break;
      case kOperandFraction:
        if (isdigit(c)) {
          op[i++] = c;
        } else {
          op[i] = '\0';
          ungetc(c, stdin);
          return kNumber;
        }
        break;
    }
  }
  return EOF;
}
