cmake_minimum_required(VERSION 3.0)
project(DM_Crypto C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-O3")
#set(CMAKE_C_FLAGS "-Wall -Werror")
set(SRCS
	./mc48.c
	./attack.c
	./main.c
	)
set(HEADERS
	./xoshiro256starstar.h
	./attack.h
	)

add_executable(test ${SRCS} ${HEADERS} )
target_link_libraries(test m)
