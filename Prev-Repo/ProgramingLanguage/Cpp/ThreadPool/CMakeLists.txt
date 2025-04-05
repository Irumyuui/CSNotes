cmake_minimum_required(VERSION 3.15)
project(thread-pool VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

add_executable(thread-pool main.cpp)

target_include_directories(thread-pool PUBLIC include)

add_compile_options(-std=c++20 -Wall -Wextra -Werror -O2 -pipe)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
