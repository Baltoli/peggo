cmake_minimum_required(VERSION 3.4.3)
project(Peggo)

add_subdirectory(src/peggo)

add_executable(peggo
  src/main.c
)

target_link_libraries(peggo
  libpeggo
)
