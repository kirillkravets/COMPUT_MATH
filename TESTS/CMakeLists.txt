cmake_minimum_required(VERSION 3.0.0)
project(COMPUTING_MATH VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)


find_package(GTest REQUIRED)


add_executable(test integration_tests.cpp)

add_test(test COMMAND integration_tests.cpp)
target_link_libraries(test gtest)

