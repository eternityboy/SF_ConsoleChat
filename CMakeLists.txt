cmake_minimum_required(VERSION 3.29)
project(SF_ConsoleChat)

set(CMAKE_CXX_STANDARD 20)

add_executable(SF_ConsoleChat main.cpp
        sources/Chat.cpp
        sources/Chat.h
        sources/Error.cpp
        sources/loadtxt.hpp)
