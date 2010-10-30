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
  Element *base;
  Element *top;
  int size;
};

// Init a empty stack.
//
// @param s, the stack object's address
// @param init_size, the stack's init size.
// @return the operation's status, 1 for ok, -2 for overflow
//         and 0 for something other error.
int InitStack(Stack *s, int init_size);
// Push an element on the top of stack s.
//
// @param s, stack address.
// @param c, the element will bu pushed.
// @return the operation's status, 1 for ok, -2 for overflow
//         and 0 for something other error.
int Push(Stack *s, Element *c);
// Pos the element on the top of stack out.
//
// @param s, stack address.
// @param c, the address to store the element poped.
// @return the operation's status, 1 for ok, -2 for overflow
//         and 0 for something other error.
int Pop(Stack *s, Element *c);

#endif