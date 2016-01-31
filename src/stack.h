# ifndef STACK_H
# define STACK_H

#include <stdbool.h>
#include "expparse.h"

# define MAX_STACK_SIZE 255

typedef ExpressionNode StackItem;

typedef struct {
  StackItem ** data;
  int currentIndex;
} Stack;

Stack * createStack();
void destroyStack(Stack * stack);

StackItem * pop(Stack * stack);
void push(Stack * stack, StackItem * item);

int size(Stack * stack);
bool isEmpty(Stack * stack);

# endif