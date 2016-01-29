# ifndef CSV_PARSE_H
# define CSV_PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CELLS 255
#define MAX_CELL_SIZE 255

typedef struct {
	char delimiter;
	int headerSize;
	char ** headers;
	char ** cells;
} CsvDescriptor;

typedef enum { DELIMITER, IN_CELL } ParserState;

void initDescriptor(CsvDescriptor * csvDescriptor);
void destroyDescriptor(CsvDescriptor * csvDescriptor);
void parseCsvLine(char * line, int size, CsvDescriptor * csvDescriptor);

#endif