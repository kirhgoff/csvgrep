# include "error.h"

void quit(char * message) {
  fprintf(stderr, "%s", message);
  exit(EXIT_FAILURE);
}
