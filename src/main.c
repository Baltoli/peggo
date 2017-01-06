#include "peggo/expression.h"

int main(int argc, char **argv) {
  peg_expr_t *g = 
    peg_sequence(
      peg_and(
        peg_not(peg_non_terminal("err")),
        peg_not(peg_non_terminal("woo"))
      ),
      peg_terminal("hello")
    );
  peg_print_expr(g);
  return 0;
}
