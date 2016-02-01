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


ExpressionNode ** parseLexems(char * query) {
  ExpressionNode ** lexems = calloc(MAX_TOKENS, sizeof(ExpressionNode*));
  int index = 0;
  char * p;
  char * varStart = query;
  for (p = query; *p != '\0'; p++) {
    if (p[0] == ' ') {
      varStart = p + 1;
      continue;
    }
    for (int i = 0; i < LEXEMS_COUNT; i ++) {
      if (prefix(LEXEMS[i], p)) {
        lexems[index] = createNode(LEXEMS_TYPE[i], LEXEMS[i]);
        index ++;
        p += sizeof(LEXEMS_TYPE[i])
        varStart = p + 1;
        continue;
      }
    }



  }
  return lexems;
}

bool prefix(const char *pre, const char *str) {
  return strncmp(pre, str, strlen(pre)) == 0;
}
