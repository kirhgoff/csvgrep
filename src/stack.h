# ifndef EXP_PARSE_H
# define EXP_PARSE_H

#include <stdbool.h>
#include "expparse.h"

# define MAX_STACK_SIZE 255

typedef struct ExpressionNode StackItem;

typedef struct _Stack {
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