# ifndef EXP_PARSE_H
# define EXP_PARSE_H

typedef enum { VALUE, COMPARISON, LOGICAL, CONST } NodeType;

//TODO think about pattern visitor here
typedef struct _ExpressionNode {
  NodeType type;
  char * value;
  char * (*evalFunc)(struct _ExpressionNode * node);

  struct _ExpressionNode * parent;

  int childrenSize;
  struct _ExpressionNode ** children;
} ExpressionNode;

# endif