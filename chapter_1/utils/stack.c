#include "stack.h"
#include <stdlib.h>
#include <string.h>

static const int kOverflow = -2;
static const int kOk = 1;
static const int kError = 0;

static const int kIncrementSize = 10;

int InitStack(Stack *s, int init_size) {
  s->base = malloc(sizeof(Element) * init_size);
  if (!s->base) {
    // Out of memory
    exit(kOverflow);
  }
  s->top = s->base;
  s->size = init_size;
  return kOk;
}

int Push(Stack *s, Element *element) {
  if (s->top - s->base >= s->size) {
    //Increase stack's memory
    s->base = realloc(s->base, (s->size + kIncrementSize) * sizeof(Element));
    if (!s->base) {
      exit(kOverflow);
    }
    s->top = s->base + s->size;
    s->size += kIncrementSize;
  }
  memcpy(s->top, element, sizeof(Element));
//  *s->top = element;
  ++s->top;
  return kOk;
}

int Pop(Stack *s, Element *element) {
  if (s->top == s->base) {
    // Empty, return error
    return kError;
  } else {
    --s->top;
    memcpy(element, s->top, sizeof(Element));
//   *element = *s->top;
    return kOk;
  }
}


