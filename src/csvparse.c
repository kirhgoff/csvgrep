#include "csvparse.h"

//------------------------------------------
// Allocates memory buffer for descriptor
//------------------------------------------
void initDescriptor(CsvDescriptor * csvDescriptor) {
  //TODO extract function
  csvDescriptor->cells = calloc(MAX_CELLS, sizeof(char*));
  for (int i = 0; i < MAX_CELLS; i++) 
    csvDescriptor->cells[i] = calloc(MAX_CELL_SIZE, sizeof(char));

  csvDescriptor->headers = calloc(MAX_CELLS, sizeof(char*));
  for (int i = 0; i < MAX_CELLS; i++) 
    csvDescriptor->cells[i] = calloc(MAX_CELL_SIZE, sizeof(char));
}

//------------------------------------------
// Free memory buffer for descriptor
//------------------------------------------
void destroyDescriptor(CsvDescriptor * csvDescriptor) {
  //TODO extract function
  for (int i = 0; i < MAX_CELLS; i++) 
    free(csvDescriptor->cells[i]);
  free(csvDescriptor->cells);

  for (int i = 0; i < MAX_CELLS; i++) 
    free(csvDescriptor->headers[i]);
  free(csvDescriptor->headers);
}

//------------------------------------------
// Parses a line into descriptor's internal buffer
//------------------------------------------
void parseCsvLine(char * line, int size, CsvDescriptor * csvDescriptor) {
  printf("Read:%s\n", line);
  char *p;
  int c;
  char * wordStart = line;
  ParserState state = IN_CELL;

  int cellIndex = 0;
  
  for (p = line; *p != '\0'; p++) {
    c = (unsigned char) *p; 
    switch (state) {
      case IN_CELL:
        if (c == csvDescriptor->delimiter) {
          state = DELIMITER;
          memcpy(csvDescriptor->cells[cellIndex], wordStart, p - wordStart);
          continue;
        }
        continue; 

      case DELIMITER: 
        if (c == csvDescriptor->delimiter) {
          continue;
        } 
        state = IN_CELL;
        wordStart = p; 
        cellIndex ++;
        continue;
    }
  }
  //Complete last word
  if (state == IN_CELL) {
    memcpy(csvDescriptor->cells[cellIndex], wordStart, p - wordStart);
  }
}
