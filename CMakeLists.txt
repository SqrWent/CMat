cmake_minimum_required(VERSION 3.20)
project(cmat C)

set(CMAKE_C_STANDARD 11)

include_directories("/usr/local/include" "/usr/local/opt/llvm/include")
link_directories("/usr/local/lib" "/usr/local/opt/llvm/lib")

add_library(cmat SHARED cmat.c Calculation/_Basic_Calculate_.c Calculation/_Basic_Calculate_.h)
