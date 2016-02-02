# include <string.h>
# include "expparse.h"
# include "error.h"


ExpressionNode * createNode(NodeType type, const char * label) {
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
  int c;
  char * p = query;
  char * varStart = NULL;
  ExpParserState state = EXP_DELIMITER;

  for (p = query; *p != '\0'; p++) {
    c = (unsigned char) * p;
    switch (state) {
      case EXP_DELIMITER:
        if (c == ' ') {
          continue;
        }
        int shift = consumeLexem(p, lexems, index);
        if (shift > 0) {
          index ++;
          p += shift;          
        } else {
          state = VAR;
          varStart = p;
        }
        continue;
      case VAR:
        if (c == ' ') {
          char * var = calloc(p - varStart, sizeof(char));
          memcpy(varStart, var, p - 1 - varStart);
          lexems[index] = createNode(TERMINAL, var);
          index ++;
          state = EXP_DELIMITER;
        }
        continue;
    }
  }
  return lexems;
}

int consumeLexem(char * p, ExpressionNode ** lexems, int index) {
  for (int i = 0; i < LEXEMS_COUNT; i ++) {
    if (prefix(LEXEMS[i], p)) {

      lexems[index] = createNode(LEXEM_TYPES[i], LEXEMS[i]);
      int length = sizeof(LEXEM_TYPES[i]);
      return length;
    }
  }
  return 0;
}

bool prefix(const char *pre, const char *str) {
  return strncmp(pre, str, strlen(pre)) == 0;
}
