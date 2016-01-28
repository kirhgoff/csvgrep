#include "csvparse.h"

void parseCsvLine(char * line, int size, CsvDescriptor * csvDescriptor) {
 printf("Read:%s\n", line);
 char *p;
 int c = (unsigned char) *p;
 char * start_of_word = p;
 ParserState state = IN_CELL;
 
 for (p = line; *p != '\0'; p++) {
   c = (unsigned char) *p; /* convert to unsigned char for is* functions */
   switch (state) {
     case IN_CELL:
       if (c == '"') {
         start_of_word = p + 1;
         state = IN_QUOTES;
         continue;
       }
       if (c == csvDescriptor->delimiter) {
         state = DELIMITER;
         //TODO process word from start_of_word to p-1          
         continue;
       }
       continue; 

     case IN_QUOTES:
       if (c == '"') {
         state = IN_CELL;
         //TODO process the word from start_of_word to p-1
         continue;
       }
       continue;

     case DELIMITER: 
       if (c == csvDescriptor->delimiter) {
         continue;
       }
       if (c == '"') {
         state = IN_CELL;
         start_of_word = p + 1; /* word starts at *next* char, not this one */
         continue;
       }
       state = IN_CELL;
       start_of_word = p; /* word starts here */
       continue;

   }
 }

 if (csvDescriptor->headerSize == 0) {
   //first run, we are initializing headers

 }
}
