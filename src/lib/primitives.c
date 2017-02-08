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
