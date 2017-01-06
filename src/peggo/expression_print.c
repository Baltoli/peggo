#include <stdio.h>

#include "expression.h"

const char *peg_expr_name(peg_expr_t *node) {
  switch(node->type) {
    case Node_Empty:
      return "Empty";
    case Node_Terminal:
      return "Terminal";
    case Node_Non_Terminal:
      return "Non-Terminal";
    case Node_Sequence:
      return "Sequence";
    case Node_Choice:
      return "Choice";
    case Node_Zero_Or_More:
      return "ZeroOrMore";
    case Node_One_Or_More:
      return "OneOrMore";
    case Node_Optional:
      return "Optional";
    case Node_And:
      return "And";
    case Node_Not:
      return "Not";
    default:
      return "INVALID";
  }
}

void print_indents(int indent) {
  for(int i = 0; i < indent; i++) {
    printf("  ");
  }
}

void peg_print_expr(peg_expr_t *node) {
  peg_print_expr_indented(node, 0);
}

void peg_print_expr_indented(peg_expr_t *node, int indent) {
  if(!node) {
    return;
  }

  print_indents(indent);
  printf("%s", peg_expr_name(node));

  if(isa(node, Node_Empty)) {
    printf("\n");
    return;
  }
  
  printf("(\n");
  
  if(node->data) {
    print_indents(indent + 1);
    printf("'%s'\n", node->data);
  }

  peg_print_expr_indented(node->left, indent+1);
  peg_print_expr_indented(node->right, indent+1);

  print_indents(indent);
  printf(")\n");
}
