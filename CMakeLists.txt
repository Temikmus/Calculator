cmake_minimum_required(VERSION 3.27)
project(calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculator main.cpp
        rational.h
        rational.cpp
        rpn.cpp
        expr.cpp
        Token.h
        Token.cpp
        Tokenizer.h
        tokenizer.cpp)
