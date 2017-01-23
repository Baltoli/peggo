if(NOT LOG_LEVEL)
  set(LOG_LEVEL 0)
endif()
add_definitions(-DDEBUG_LEVEL=${LOG_LEVEL})

add_library(peggo
  expression_construct.c
  expression_print.c
  rule.c
  grammar.c
  parse_tree.c
  common.c
  parser.c
  log.c
)

set(headers
  expression.h
  parser.h
  parse_tree.h
  rule.h
  grammar.h
  peggo.h
)
set_target_properties(peggo
  PROPERTIES PUBLIC_HEADER "${headers}"
)

install(
  TARGETS peggo
  LIBRARY DESTINATION lib/peggo
  ARCHIVE DESTINATION lib/peggo
  PUBLIC_HEADER DESTINATION include/peggo
)
