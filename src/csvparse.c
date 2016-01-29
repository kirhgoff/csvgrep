#include "csvparse.h"

//------------------------------------------
// Allocates memory buffer for descriptor
//------------------------------------------
char ** initCellsStorage () {
  char ** pointer = calloc(MAX_CELLS, sizeof(char*));
  for (int i = 0; i < MAX_CELLS; i++)
    pointer[i] = calloc(MAX_CELL_SIZE, sizeof(char));
  return pointer;
}

void initDescriptor(CsvDescriptor * csvDescriptor) {
  csvDescriptor->cells = initCellsStorage();
  csvDescriptor->headers = initCellsStorage();
}

//------------------------------------------
// Free memory buffer for descriptor
//------------------------------------------
void freeCellsStorage(char ** pointer) {
  for (int i = 0; i < MAX_CELLS; i++) free(pointer[i]);
  free(pointer);
}

void destroyDescriptor(CsvDescriptor * csvDescriptor) {
  freeCellsStorage(csvDescriptor->cells);
  freeCellsStorage(csvDescriptor->headers);
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
    c = (unsigned char) * p;
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
