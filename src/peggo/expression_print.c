#include <stdio.h>

#include "common.h"
#include "expression.h"

const char *expr_name(expr_t *node) {
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

void print_expr(expr_t *node) {
  print_expr_indented(node, 0);
}

void print_expr_indented(expr_t *node, int indent) {
  if(!node) {
    return;
  }

  print_indents(indent);
  printf("%s", expr_name(node));

  if(isa(node, Node_Empty)) {
    printf("\n");
    return;
  }
  
  printf("(\n");
  
  if(node->data) {
    print_indents(indent + 1);
    printf("'%s'\n", node->data);
  }

  print_expr_indented(node->left, indent+1);
  print_expr_indented(node->right, indent+1);

  print_indents(indent);
  printf(")\n");
}
