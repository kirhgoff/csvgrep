#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "csvparse.h"

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



//---------------------------------------------------
// MAIN
//---------------------------------------------------
int main(int argc, char **argv) {
  //----- Working part
  // Args args;
  // parseArguments(&args, argc, argv);

 // FILE *stream = resolveStream(&args);
 // readByLine(stream, parseLine);
 // closeStream(stream);
 //---------Tests-------
  // char * sampleCsvLines[2] = {"a;b;c", "00;11;22"};
  // //TODO make default value
  // CsvDescriptor csvDescriptor = {';', 0, null};
  
  // for (int i = 0; i < 2; i ++) {
  //   char * line = sampleCsvLines[i];
  //   parseLine(line, sizeof(line), &csvDescriptor);
  // }
 
 exit(EXIT_SUCCESS);
}