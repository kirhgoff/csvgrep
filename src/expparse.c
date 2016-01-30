# include <string.h>
# include "expparse.h"
# include "error.h"

ExpressionNode * createNode(NodeType type, char * label) {
  ExpressionNode * node = calloc(1, sizeof(ExpressionNode));
  node->type = type;
  node->label = label;
  return node;
};

void destroyNode(ExpressionNode * node) {
  if (node == NULL) quit("expparse.destroyNode invalid argument NULL");
  free(node);
};

bool equals(ExpressionNode * first, ExpressionNode * second) {
  if (first == second) return true;
  if (first == NULL || second == NULL) return false;

  if (first->type != second->type) return false;
  if (first->label == second->label) return true;
  if (first->label == NULL || second->label == NULL) return false;
  if (strcmp(first->label, second->label) != 0) return false;

  return true;
};
