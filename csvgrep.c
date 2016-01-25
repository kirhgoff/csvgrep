#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

//---------------------------------------------------
// Arguments parsing
//---------------------------------------------------

typedef struct  {
  char * delimiter;
  char * fileName;
}  Args;

void printArgs(Args * args) {
  printf("delimiter=%s fileName=%s\n", args->delimiter, args->fileName);
};

void printUsageAndExit() {
  printf("Usage: csvgrep -d 'delimiter' [-f 'fileName']\n");
  exit(EXIT_SUCCESS);
}

void parseArguments(Args * args, int argc, char **argv) {
  int opt;
  while ((opt = getopt(argc, argv, "d:f:")) != -1) {
    switch (opt) {
      case 'd':        
        args->delimiter = optarg;
        break;        
      case 'f':
        args->fileName = optarg;
        break;
      default:
        printUsageAndExit();
    }
  }
  printArgs(args);
}


//---------------------------------------------------
// Methods to work with streams
//---------------------------------------------------

FILE * resolveStream(Args * args) {
  if (args->fileName == NULL) {
    return stdin;
  } else {
    FILE * stream = fopen(args->fileName, "r");
    if (stream == NULL) {
      printf("Cannot open file, exiting.\n");
      exit(EXIT_FAILURE);
    }
    return stream;
  }
}

void closeStream(FILE * stream) {
  if (stream != stdin && stream != NULL) {
    fclose(stream);
  }
}

void readByLine(FILE * stream, void (*callback)(char *, int)) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, stream)) != -1) {
    // printf("Retrieved line of length %zu :\n", read);
    // printf("%s", line);
    (*callback)(line, read);
  }

  free(line);
}

//---------------------------------------------------
// CSV parsing
//---------------------------------------------------
typedef struct {
  char delimiter;
  int headerSize;
  char ** headerNames;
} CsvDescriptor;

enum states { DELIMITER, IN_CELL, IN_QUOTES } state = IN_CELL;

void parseLine(char * line, int size, CsvDescriptor * csvDescriptor) {
  printf("Read:%s\n", line);
  char *p;
  int c = (unsigned char) *p;
  char * start_of_word = p;

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

      case DULL: 
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


//---------------------------------------------------
// MAIN
//---------------------------------------------------
int main(int argc, char **argv) {
  //----- Working part
 //  Args args;
 //  parseArguments(&args, argc, argv);

 // FILE *stream = resolveStream(&args);
 // readByLine(stream, parseLine);
 // closeStream(stream);
 //---------Tests-------
  char * sampleCsvLines[2] = {"a;b;c", "00;11;22"};
  //TODO make default value
  CsvDescriptor csvDescriptor = {';', 0, null};
  
  for (int i = 0; i < 2; i ++) {
    char * line = sampleCsvLines[i];
    parseLine(line, sizeof(line), &csvDescriptor);
  }
 
 exit(EXIT_SUCCESS);
}