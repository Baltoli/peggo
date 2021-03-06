#include "primitives.h"

expr_t *sep_by(expr_t *e, expr_t *s) {
  return optional(
    sequence(
      e,
      zero_or_more(
        sequence(s, e)
      )
    )
  );
}

expr_t *whitespace() {
  return zero_or_more(
    choice(
      terminal(" "),
      terminal("\t")
    )
  );
}

expr_t *wrapped(expr_t *left, expr_t *inner, expr_t *right) {
  return sequence(
    sequence(
      left,
      inner
    ),
    right
  );
}
