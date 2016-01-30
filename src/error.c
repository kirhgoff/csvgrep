# include "error.h"

void quit(char * message) {
  fprintf(stderr, message);
  exit(EXIT_FAILURE);
}
