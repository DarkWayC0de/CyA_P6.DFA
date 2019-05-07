cmake_minimum_required(VERSION 3.13)
project(P6__1__DFA)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(P6__1__DFA
        dfa_t.cpp
        dfa_t.h
        estados.cpp
        estados.h
        main.cpp)
