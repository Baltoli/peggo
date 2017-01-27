#include <stdio.h>
#include <stdlib.h>

#include "log.h"

char *level_to_string(unsigned int level) {
  switch(level) {
    case 1:
      return "error";
    case 2:
      return "warning";
    case 3:
      return "info";
    case 4:
      return "debug";
    default:
      return "invalid log level";
  }
}

void fatal_error(char *message) {
  fprintf(stderr, "[libpeggo FATAL]: %s\n", message);
  exit(EXIT_FAILURE);
}

void log_level(unsigned int level, char *message) {
  if(level <= DEBUG_LEVEL) {
    fprintf(stderr, "libpeggo [%s]: %s\n", level_to_string(level), message);
  }
}
