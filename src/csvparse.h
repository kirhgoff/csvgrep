# ifndef CSV_PARSE_H
# define CSV_PARSE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
   char delimiter;
   int headerSize;
   char ** headerNames;
 } CsvDescriptor;

typedef enum { DELIMITER, IN_CELL, IN_QUOTES } ParserState;

void parseCsvLine(char * line, int size, CsvDescriptor * csvDescriptor);

#endif