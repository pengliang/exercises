#ifndef K_AND_R_ASSIGNMENTS_UTILS_STACK_H_
#define K_AND_R_ASSIGNMENTS_UTILS_STACK_H_

/*
struct Element {
  char c;
  int line;
  int col;
};

typedef struct Element Element;
*/

typedef double Element;

struct Stack {
  Element *base_;
  Element *top_;
  int size_;
};

typedef struct Stack Stack;

extern const int kOk;
extern const int kOverflow;
extern const int kError;

// Initializes an empty stack.
//
// @param self the stack object's address.
// @param init_size the stack's init size.
// @return 1 for success,
//         0 for memory overflow
int StackInit(Stack *self, int init_size);

// Destroys a stack object.
//
// @param self the stack object's address.
void StackDestroy(Stack *self);

// Clear a stack
// @param self the stack object's address.
void StackClear(Stack *self);

// Pushes an element on the top of stack s.
//
// @param self stack address.
// @param c the element will bu pushed.
// @return 1 for success,
//         0 for memory overflow
int StackPush(Stack *self, Element *c);

// Pops the element on the top of stack out.
//
// @param self stack address.
// @param[out] c the address to store the element pop out.
// @return 1 for success,
//         0 for empty stack.
int StackPop(Stack *self, Element *c);

// Returns a stack is empty or not.
//
// @param self stack object's address.
// @return 1 for empty stack,
//         0 for not.
int StackIsEmpty(Stack *self);

// Gets a stack's size.
//
// @param self stack object's address.
// @return stack's size.
int StackGetSize(Stack *self);

#endif // K_AND_R_ASSIGNMENTS_UTILS_STACK_H_
