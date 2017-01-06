cmake_minimum_required(VERSION 2.8)
project(Peggo)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

add_subdirectory(src/peggo)

add_executable(main
  src/main.c
)

target_link_libraries(main
  peggo
)
