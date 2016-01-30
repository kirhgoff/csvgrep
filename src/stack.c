# include <string.h>
# include "stack.h"
# include "error.h"

Stack * createStack() {
  Stack * stack = calloc(1, sizeof(Stack));
  stack->data = calloc (MAX_STACK_SIZE, sizeof(StackItem*));
  stack->currentIndex = -1;
  return stack;
}

void destroyStack(Stack * stack) {
  if (stack == NULL) quit("stack.destroyStack: incorrect parameter NULL");
  free(stack->data);
  free(stack);
};

StackItem * pop(Stack * stack) {
  if (stack == NULL) quit("stack.pop: incorrect parameter NULL");
  if (isEmpty(stack)) return NULL;
  StackItem * lastItem = stack->data[stack->currentIndex];
  stack->currentIndex -= 1;
  return lastItem;
};

void push(Stack * stack, StackItem * item) {
  if (stack == NULL) quit("stack.push: incorrect parameter NULL");
  if (size(stack) >= MAX_STACK_SIZE - 1) quit("stack.push: stack overflow"); 
  stack->currentIndex += 1;
  stack->data[stack->currentIndex] = item;
};

int size(Stack * stack) {
  if (stack == NULL) quit("stack.size: incorrect parameter NULL");
  return stack->currentIndex + 1;
};

bool isEmpty(Stack * stack) {
  if (stack == NULL) quit("stack.isEmpty: incorrect parameter NULL");
  return stack->currentIndex == -1;
};
