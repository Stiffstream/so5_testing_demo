cmake_minimum_required(VERSION 3.10)

set(PRJ _utest_dining_philosophers_app)

project(${PRJ})

add_executable(${PRJ} main.cpp)
target_link_libraries(${PRJ} sobjectizer::StaticLib)

add_test(NAME ${PRJ} COMMAND ${PRJ})

