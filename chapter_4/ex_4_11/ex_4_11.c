#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "utils/stack.h"

// Signal that a number was found
#define NUMBER '0'
#define FUNCTION 'f'

// Max size of operand and operator
static const int kMaxOp = 100;
// The number of variables that our calculator can process.
static const int kVarNum = 26;
static const int kStackInitSize = 100;

enum PaserState {
  kStart,
  kFunction,
  kOperandInteger,
  kOperandFraction,
  kMinus,
  kPlus
};

/* Gets the next operator or numeric operand */
int GetOp(char op[]) {
  char c;
  enum PaserState state = kStart;
  int i  = 0;
  static int lastc = 0;

  while (1) {
    if (lastc == 0) {
      c = getchar();
      if (c == EOF) {
        break;
      }
    } else {
      c = lastc;
      lastc = 0;
    }
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
          lastc = c;
          if (i > 1) {
            return FUNCTION;
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
          lastc = c;
          return '-';
        }
        break;
      case kPlus:
        if (isdigit(c)) {
          op[i++] = '+';
          op[i++] = c;
          state = kOperandInteger;
        } else {
          lastc = c;
          return '+';
        }
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
              lastc = c;
              return NUMBER;
          }
        }
        break;
      case kOperandFraction:
        if (isdigit(c)) {
          op[i++] = c;
        } else {
          op[i] = '\0';
          lastc = c;
          return NUMBER;
        }
        break;
    }
  }
  return EOF;
}

/* Checks string operand for supported math functions */
void MathFunc(Stack *stack, char func[]) {
  double op;

  StackPop(stack, &op);
  if (strcmp(func, "sin") == 0) {
    op = sin(op);
  } else if (strcmp(func, "cos") == 0) {
    op = cos(op);
  } else if (strcmp(func, "exp") == 0) {
    op = exp(op);
  } else if (strcmp(func, "pow") == 0) {
    double op2;
    StackPop(stack, &op2);
    op = pow(op2, op);
  } else {
    printf("Error: function %s not supported\n", func);
  }
  StackPush(stack, &op);
}

/* Reverse Polish calculator */
int main() {
  int op_type, i = 0, var = 0;
  double op2;
  char operand[kMaxOp];
  double variable[kVarNum];
  // variable v to store the value printed recently.
  double v;
  Stack stack;

  StackInit(&stack, kStackInitSize);

  for (i = 0; i < kVarNum; i++) {
    variable[i] = 0.0;
  }

  while ((op_type = GetOp(operand)) != EOF) {
    switch (op_type) {
      double op;
      case NUMBER:
        op = atof(operand);
        StackPush(&stack, &op);
        break;
      case FUNCTION:
        MathFunc(&stack, operand);
        break;
      case '=':
        StackPop(&stack, &op);
        StackPop(&stack, &op);
        if (var >= 'A' && var <= 'Z') {
          variable[var - 'A'] = op; 
        } else {
          printf("Error: not valid variable name\n");
        }
        break;
      case '+':
        StackPop(&stack, &op);
        StackPop(&stack, &op2);
        op = op + op2;
        StackPush(&stack, &op);
        break;
      case '-':
        StackPop(&stack, &op);
        StackPop(&stack, &op2);
        op = op2 -  op;
        StackPush(&stack, &op);
        break;
      case '*':
        StackPop(&stack, &op);
        StackPop(&stack, &op2);
        op = op2 * op;
        StackPush(&stack, &op);
        break;
      case '/':
        StackPop(&stack, &op);
        StackPop(&stack, &op2);
        if (op != 0.0) {
          op = op2 / op;
          StackPush(&stack, &op);
        } else {
          printf("Error: zero divisor\n");
        }
        break;
      case '%':
        StackPop(&stack, &op);
        StackPop(&stack, &op2);
        if (op != 0.0) {
          op = fmod(op2, op);
          StackPush(&stack, &op);
        } else {
          printf("Error: zero divisor\n");
        }
        break;
      case '\n':
        StackPop(&stack, &op);
        v = op;
        printf("%.8f\n", op);
        break;
      case '?': /* Prints top element of the stack */
        StackPop(&stack, &op);
        printf("%.8f\n", op);
        StackPop(&stack, &op);
        break;
      case 'c': /* Clear the stack */
        StackClear(&stack);
        break;
      case 'd': /* Duplicates tope elements of the stack */
        StackPop(&stack, &op);
        StackPush(&stack, &op);
        StackPush(&stack, &op);
        break;
      case 's': /* Swaps the top two elements */
        StackPop(&stack, &op);
        StackPop(&stack, &op2);
        StackPush(&stack, &op);
        StackPush(&stack, &op2);
        break;
      case 'v':
        StackPush(&stack, &v);
        break;
      default:
        if (op_type >= 'A' && op_type <= 'Z') {
          var = op_type;
          StackPush(&stack, variable + op_type - 'A');
        } else {
          printf("Error: unknown command \n");
        }
        break;
    }
  }
  return 0;
}
