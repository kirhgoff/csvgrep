# include <string.h>
# include "expparse.h"
# include "error.h"

//TODO add another method to copy from pointer
ExpressionNode * createNode(NodeType type, const char * label) {
  ExpressionNode * node = calloc(1, sizeof(ExpressionNode));
  node->type = type;
  node->label = calloc(MAX_TOKEN_LENGTH, sizeof(char));
  memcpy(node->label, label, strlen(label));
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
  int ordinal = -1;
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
        ordinal = detectLexem(p);
        if (ordinal != -1) {
          lexems[index] = createNode(LEXEM_TYPES[ordinal], LEXEMS[ordinal]);
          index ++;
          p += strlen(LEXEMS[ordinal])-1;
          //state keeps the same          
        } else {
          state = VAR;
          varStart = p;
        }
        continue;
      case VAR:
        if (c == ' ') {
          //consume var
          lexems[index] = createVar(p, varStart);
          index ++;
          state = EXP_DELIMITER;
          continue;
        }
        ordinal = detectLexem(p);
        if (ordinal != -1) {
          //consume var
          lexems[index] = createVar(p, varStart);
          index ++;

          //consume lexem
          const char * lexem = LEXEMS[ordinal];
          lexems[index] = createNode(LEXEM_TYPES[ordinal], lexem);
          index ++;
          p += strlen(lexem) - 1; //Should point at the end of lexem          

          state = EXP_DELIMITER;
        }
        continue;
    }
  }

  //consume last var
  if (state == VAR) {
    char * var = calloc(p - varStart, sizeof(char));
    memcpy(var, varStart, p - varStart);
    lexems[index] = createNode(TERMINAL, var);
  }
  return lexems;
}

ExpressionNode * createVar(char * end, char * start) {
  char * var = calloc(end - start, sizeof(char));
  memcpy(var, start, end - start);
  return createNode(TERMINAL, var);
}

int detectLexem(char * p) {
  for (int i = 0; i < LEXEMS_COUNT; i ++) {
    if (prefix(LEXEMS[i], p)) {
      return i;
    }
  }
  return -1;
}

bool prefix(const char *pre, const char *str) {
  return strncmp(pre, str, strlen(pre)) == 0;
}
