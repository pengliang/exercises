#include "stack.h"
#include <stdlib.h>
#include <string.h>

const int kOk = 1;
const int kError = 0;

static const int kIncrementSize = 10;

int StackInit(Stack *s, int init_size) {
  s->base_ = malloc(sizeof(Element) * init_size);
  if (!s->base_) {
    // Out of memory
   return kError;
  }
  s->top_ = s->base_;
  s->size_ = init_size;
  return kOk;
}

void StackDestroy(Stack *s) {
  free(s->base_);
}

void StackClear(Stack *s) {
  s->top_ = s->base_;
}

int StackGetSize(Stack *s) {
  return s->size_;
}

int StackIsEmpty(Stack *s) {
  return s->top_ == s->base_;
}

int StackPush(Stack *s, Element *element) {
  if (s->top_ - s->base_ >= s->size_) {
    //Increase stack's memory
    s->base_ = realloc(s->base_,
                       (s->size_ + kIncrementSize) * sizeof(Element));
    if (!s->base_) {
      return kError;
    }
    s->top_ = s->base_ + s->size_;
    s->size_ += kIncrementSize;
  }
  memcpy(s->top_, element, sizeof(Element));
  ++s->top_;
  return kOk;
}

int StackPop(Stack *s, Element *element) {
  if (s->top_ == s->base_) {
    // Empty, return error
    return kError;
  } else {
    --s->top_;
    memcpy(element, s->top_, sizeof(Element));
    return kOk;
  }
}
