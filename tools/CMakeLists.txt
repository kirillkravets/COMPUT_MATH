cmake_minimum_required(VERSION 3.0.0)
project(COMPUTING_MATH VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Werror)

file(GLOB_RECURSE source *.hpp *.cpp)
add_library(tools_lib INTERFACE ${source})
