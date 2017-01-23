#include <stdio.h>
#include <stdlib.h>

#include "log.h"

void fatal_error(char *message) {
  fprintf(stderr, "libpeggo fatal error: %s\n", message);
  exit(EXIT_FAILURE);
}
