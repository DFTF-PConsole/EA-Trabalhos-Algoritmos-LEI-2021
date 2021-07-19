cmake_minimum_required(VERSION 3.19)
project(ProjAux)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra")

add_executable(ProjAux main.cpp header_testes.h header_trab.h testes.cpp trab.cpp)