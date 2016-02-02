# ifndef EXP_PARSE_H
# define EXP_PARSE_H

# include <stdbool.h>

# define MAX_TOKENS 1024
/*
 EXPRESSIONS
 
 market='FX'
 market='FX' AND underlyingCode='USD' AND currentPrice=''
 underlyingCode='USD' OR underlyingCode='EUR'
 market='FX' AND (underlyingCode='USD' OR underlyingCode='EUR')
 
 GRAMMAR

 E -> P B P
 P -> t | "(" E ")"  
 B -> "AND" | "OR" | "="

*/

typedef enum { TERMINAL, COMPARISON, LOGICAL, BRACE } NodeType;
typedef enum { EXP_DELIMITER, VAR } ExpParserState;

//These two arrays should correspond each other
# define LEXEMS_COUNT 5 

static const char* LEXEMS[LEXEMS_COUNT] = {
  "=", // COMPARISON
  "AND", //LOGICAL
  "OR", //LOGICAL
  "(", //BRACE
  ")", //BRACE  
};

static const NodeType LEXEM_TYPES[LEXEMS_COUNT] = {
  COMPARISON, //"=" 
  LOGICAL, //"AND"
  LOGICAL, //"OR"
  BRACE, //"("
  BRACE //")"
};

typedef struct _ExpressionNode {
  NodeType type;
  const char * label;

  struct _ExpressionNode * parent;
  struct _ExpressionNode ** children;
  int childrenSize;

  char * (*evalFunc)(struct _ExpressionNode * node);

} ExpressionNode;

ExpressionNode * createNode(NodeType type, const char * label);
void destroyNode(ExpressionNode * node);

bool equals(ExpressionNode * first, ExpressionNode * second);

bool prefix(const char *pre, const char *str);
ExpressionNode ** parseLexems(char * query);
int detectLexem(char * p);

# endif