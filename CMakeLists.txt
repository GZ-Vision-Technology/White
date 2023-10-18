cmake_minimum_required(VERSION 3.17)

project(White VERSION 1.0
        DESCRIPTION "The White Framework"
        LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Src)

option(FLOAT_AS_DOUBLE "Use 64-bits floats" OFF)

add_executable(White White.cpp)