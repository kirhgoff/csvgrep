#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

//----------------------------------------------------
// Data structures
//----------------------------------------------------
struct Args_type {
  char * delimiter;
  char * fileName;
} ;

typedef struct Args_type Args;

void print(Args * args) {
  printf("delimiter=%s fileName=%s\n", args->delimiter, args->fileName);
};

//---------------------------------------------------
// Checks whether are we reading from stdin or from file
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

//---------------------------------------------------
// Close stream if it is a file
//---------------------------------------------------
void closeStream(FILE * stream) {
  if (stream != stdin && stream != NULL) {
    fclose(stream);
  }
}

//---------------------------------------------------
// reads line by line and calls a callback
// frees the line pointer after work
//---------------------------------------------------
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
// Parses the csv
//---------------------------------------------------
void parseLine(char * line, int size) {
  printf("Read:%s", line);
}

//---------------------------------------------------
// Print usage and exit
//---------------------------------------------------

void printUsageAndExit() {
  printf("Usage: csvgrep -d 'delimiter' [-f 'fileName']\n");
  exit(EXIT_SUCCESS);
}

//---------------------------------------------------
// Process args
//---------------------------------------------------
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
  print(args);
}
//---------------------------------------------------
// MAIN
//---------------------------------------------------
int main(int argc, char **argv) {
  Args args;
  parseArguments(&args, argc, argv);

 FILE *stream = resolveStream(&args);
 readByLine(stream, parseLine);
 closeStream(stream);
 
 exit(EXIT_SUCCESS);
}