#include <stdio.h>
#include <stdlib.h>

#include "log.h"

FILE *log_file = NULL;

FILE *get_log_file() {
  if(log_file) {
    return log_file;
  }

  return stderr;
}

void log_redirect(FILE *f) {
  log_file = f;
}

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
  fprintf(get_log_file(), "[libpeggo FATAL]: %s\n", message);
  exit(EXIT_FAILURE);
}

void log_level(unsigned int level, char *message) {
  if(level <= DEBUG_LEVEL) {
    fprintf(get_log_file(), "libpeggo [%s]: %s\n", level_to_string(level), message);
  }
}
