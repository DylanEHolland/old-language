cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(liz)

add_library(frontend
    include/frontend/parser.h
    include/frontend/tokenize.h
    source/frontend/parser.cc
    source/frontend/tokenize.cc
)

add_library(vm
    include/backend/vm/instructions.h
    source/backend/vm/instructions.cc
)

add_library(lizasm
    include/backend/assembler/assembler.h
    source/backend/assembler/assembler.cc
)

target_include_directories(
    frontend
    PUBLIC
        "include"
)

target_include_directories(
    vm
    PUBLIC
        "include"
)

add_executable(liz
  source/main.cc
)

add_executable(lizvm
  source/lizvm.cc
)

target_link_libraries(liz frontend vm lizasm)
target_link_libraries(lizvm vm lizasm)