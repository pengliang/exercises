#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "utils/stack.h"
#include "getopt.h"

// Signal that a number was found
#define NUMBER '0'
#define FUNCTION 'f'

// Max size of operand and operator
static const int kMaxOp = 100;
// The number of variables that our calculator can process.
static const int kVarNum = 26;
static const int kStackInitSize = 100;

/* Pops top element on the stack*/
static inline void Pop(Stack *stack, Element *top) {
  if (!StackPop(stack, top)) {
    printf("Error: empty stack.");
    exit(1);
  }
}

/* Pushed an element on the stack */
static inline void Push(Stack *stack, Element *top) {
  if (!StackPush(stack, top)) {
    printf("Error: memory overflow!");
    exit(1);
  }
}

/* Checks string operand for supported math functions */
static inline void MathFunc(Stack *stack, char func[]) {
  double op;

  Pop(stack, &op);
  if (strcmp(func, "sin") == 0) {
    op = sin(op);
  } else if (strcmp(func, "cos") == 0) {
    op = cos(op);
  } else if (strcmp(func, "exp") == 0) {
    op = exp(op);
  } else if (strcmp(func, "pow") == 0) {
    double op2;
    Pop(stack, &op2);
    op = pow(op2, op);
  } else {
    printf("Error: function %s not supported\n", func);
    exit(1);
  }
  Push(stack, &op);
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

  while ((op_type = GetOpt(operand)) != EOF) {
    switch (op_type) {
      double op;
      case NUMBER:
        op = atof(operand);
        Push(&stack, &op);
        break;
      case FUNCTION:
        MathFunc(&stack, operand);
        break;
      case '=':
        Pop(&stack, &op);
        if (var >= 'A' && var <= 'Z') {
          variable[var - 'A'] = op; 
        } else {
          printf("Error: not valid variable name\n");
          exit(1);
        }
        break;
      case '+':
        Pop(&stack, &op);
        Pop(&stack, &op2);
        op = op + op2;
        Push(&stack, &op);
        break;
      case '-':
        Pop(&stack, &op);
        Pop(&stack, &op2);
        op = op2 -  op;
        Push(&stack, &op);
        break;
      case '*':
        Pop(&stack, &op);
        Pop(&stack, &op2);
        op = op2 * op;
        Push(&stack, &op);
        break;
      case '/':
        Pop(&stack, &op);
        Pop(&stack, &op2);
        if (op != 0.0) {
          op = op2 / op;
          Push(&stack, &op);
        } else {
          printf("Error: zero divisor\n");
          exit(1);
        }
        break;
      case '%':
        Pop(&stack, &op);
        Pop(&stack, &op2);
        if (op != 0.0) {
          op = fmod(op2, op);
          Push(&stack, &op);
        } else {
          printf("Error: zero divisor\n");
          exit(1);
        }
        break;
      case '\n':
        Pop(&stack, &op);
        v = op;
        printf("%.8f\n", op);
        break;
      case '?': /* Prints top element of the stack */
        Pop(&stack, &op);
        printf("%.8f\n", op);
        Pop(&stack, &op);
        break;
      case 'c': /* Clear the stack */
        StackClear(&stack);
        break;
      case 'd': /* Duplicates tope elements of the stack */
        Pop(&stack, &op);
        Push(&stack, &op);
        Push(&stack, &op);
        break;
      case 's': /* Swaps the top two elements */
        Pop(&stack, &op);
        Pop(&stack, &op2);
        Push(&stack, &op);
        Push(&stack, &op2);
        break;
      case 'v':
        Push(&stack, &v);
        break;
      default:
        if (op_type >= 'A' && op_type <= 'Z') {
          var = op_type;
          Push(&stack, variable + op_type - 'A');
        } else {
          printf("Error: unknown command \n");
          exit(1);
        }
        break;
    }
  }
  return 0;
}
