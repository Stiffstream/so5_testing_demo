cmake_minimum_required(VERSION 3.10)

set(PRJ ping_pong_app)

project(${PRJ})

add_executable(${PRJ} main.cpp)
target_link_libraries(${PRJ} sobjectizer::StaticLib)

install(
	TARGETS ${PRJ}
	RUNTIME DESTINATION bin
)

