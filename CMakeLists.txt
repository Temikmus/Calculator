cmake_minimum_required(VERSION 3.27)
project(calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculator main.cpp
        rational.h
        rational.cpp
        rpn.cpp
        Token.h
        Token.cpp
        tokenizer.cpp
        rpn.h
        tokenizer.h
        funcs.cpp
        NOD
        sqrt
        "remainder of division"
        expr.cpp
        simple
        math_functions.h
)
