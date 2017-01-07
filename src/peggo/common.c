#include <stdio.h>

#include "common.h"

void print_indents(int indent) {
  for(int i = 0; i < indent; i++) {
    printf("  ");
  }
}
