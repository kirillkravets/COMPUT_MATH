cmake_minimum_required(VERSION 3.0.0)
project(COMPUTING_MATH VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

#enable_testing()

add_compile_options(-Wall -Werror)

add_subdirectory(source)
add_subdirectory(TESTS)

add_library(comput_math_lib INTERFACE ${source})