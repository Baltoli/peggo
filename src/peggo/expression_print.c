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
