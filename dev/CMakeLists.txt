cmake_minimum_required(VERSION 3.10)

project(so5_testing_demo CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOBJECTIZER_BUILD_SHARED OFF)
set(SOBJECTIZER_BUILD_STATIC ON)

add_subdirectory(so_5)

enable_testing()
add_subdirectory(tests)

add_subdirectory(ping_pong)
add_subdirectory(dining_philosophers)

