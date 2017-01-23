#include <stdio.h>
#include <stdlib.h>

#include "log.h"

void fatal_error(char *message) {
  fprintf(stderr, "libpeggo fatal error: %s\n", message);
  exit(EXIT_FAILURE);
}

void log_level(unsigned int level, char *message) {
  if(level <= DEBUG_LEVEL) {
    fprintf(stderr, "libpeggo [%s]: %s\n", "placeholder", message);
  }
}
