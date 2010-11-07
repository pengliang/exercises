#ifndef K_AND_R_ASSIGNMENTS_CHAPTER_1_UTILS_STACK_H_
#define K_AND_R_ASSIGNMENTS_CHAPTER_1_UTILS_STACK_H_

struct Element;
struct Stack;

typedef struct Element Element;
typedef struct Stack Stack;

struct Element {
  char c;
  int line;
  int col;
};

struct Stack {
  Element *base_;
  Element *top_;
  int size_;
};

// Init an empty stack.
//
// @param s, the stack object's address.
// @param init_size, the stack's init size.
// @return the operation's status, 1 for ok, -2 for memory overflow
//         and 0 for something other error.
int StackInit(Stack *s, int init_size);
// Destroy a stack object.
//
// @param s, the stack object's address.
// @return 1 for ok, 0 for something error.
int StackDestroy(Stack *s);
// Push an element on the top of stack s.
//
// @param s, stack address.
// @param c, the element will bu pushed.
// @return the operation's status, 1 for ok, -2 for memory overflow
//         and 0 for something other error.
int StackPush(Stack *s, Element *c);
// Pop the element on the top of stack out.
//
// @param s, stack address.
// @param[out] c, the address to store the element pop out.
// @return the operation's status, 1 for ok, 0 for something error.
int StackPop(Stack *s, Element *c);
// Return a stack is empty or not.
//
// @param s, stack object's address.
// @return 1 for empty stack, 0 for not.
int StackIsEmpty(Stack *s);
// Return a stack's size.
//
// @param s, stack object's address.
// @return stack's size.
int StackGetSize(Stack *s);
#endif
