add_executable(parser_unit_tests 
  main.c
  test_parser.c
  test_parser_empty.c
  test_parser_terminal.c
  test_parser_non_terminal.c
  test_parser_sequence.c
  test_parser_choice.c
  test_parser_zero.c
  test_parser_one.c
  test_parser_optional.c
  test_parser_and.c
  test_parser_not.c
  test_parser_sep_by.c
  test_parser_whitespace.c
  test_parser_wrapped.c
)
target_link_libraries(parser_unit_tests ${CMOCKA_LIBRARY} peggo)

add_executable(iterator_unit_tests
  iterator_main.c
  test_iterators.c
)
target_link_libraries(iterator_unit_tests ${CMOCKA_LIBRARY} peggo)


add_test(
  NAME "ParserUnitTests"
  COMMAND ${CMAKE_BINARY_DIR}/test/parser_unit_tests
)

add_test(
  NAME "IteratorUnitTests"
  COMMAND ${CMAKE_BINARY_DIR}/test/iterator_unit_tests
)
