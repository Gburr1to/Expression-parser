cmake_minimum_required(VERSION 4.0)
project(nal2)

set(CMAKE_CXX_STANDARD 14)

add_executable(parser
        main.cpp
        Token.h
        Scanner.h)
