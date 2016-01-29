#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "csvparse.h"

//---------------------------------------------------
// Arguments parsing
//---------------------------------------------------

#define DEFAULT_DELIMITER ";"

typedef struct  {
  char * delimiter;
  char * fileName;
  char * expression;
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
  while ((opt = getopt(argc, argv, "d:f:e:")) != -1) {
    switch (opt) {
    case 'd':
      args->delimiter = optarg;
      break;
    case 'f':
      args->fileName = optarg;
      break;
    case 'e':
      args->expression = optarg;
      break;
    default:
      printUsageAndExit();
    }
  }
  if (args->delimiter == NULL) {
    args->delimiter = DEFAULT_DELIMITER;
  }
  //printArgs(args);
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

void readByLine(FILE * stream, void (*callback)(char *, int, CsvDescriptor*), CsvDescriptor * csv) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, stream)) != -1) {
    (*callback)(line, read, csv);
  }

  free(line);
}

//---------------------------------------------------
// MAIN
//---------------------------------------------------
int main(int argc, char **argv) {
  Args args;
  parseArguments(&args, argc, argv);
  //TODO add macros for csvparse
  CsvDescriptor csv = {*args.delimiter, 0, NULL, NULL};

  FILE *stream = resolveStream(&args);
  readByLine(stream, parseCsvLine, &csv);
  closeStream(stream);

  exit(EXIT_SUCCESS);
}