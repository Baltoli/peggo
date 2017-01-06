#include "expression_p.h"
#include "expression.h"

peg_expr_t node_init() {
  peg_expr_t node;
  return node;
}

peg_expr_t node_empty() {
  peg_expr_t node = node_init();
  node.type = Node_Empty;
  return node;
}
