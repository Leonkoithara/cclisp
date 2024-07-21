cmake_minimum_required(VERSION 3.16.3)

project(cclisp)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(cclc src/main.c)
add_library(lex src/lex.c)
add_library(semantic src/semantic.c)

target_include_directories(
  cclc
  PUBLIC
  src/include
  )
target_link_libraries(
  cclc
  lex
  semantic
  )
target_include_directories(
  lex
  PUBLIC
  src/include
  )
target_include_directories(
  semantic
  PUBLIC
  src/include
  )
