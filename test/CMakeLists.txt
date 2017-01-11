add_executable(unit_tests 
  main.c
  test_parser.c
  test_parser_empty.c
  test_parser_terminal.c
  test_parser_non_terminal.c
)
target_link_libraries(unit_tests cmocka peggo)
