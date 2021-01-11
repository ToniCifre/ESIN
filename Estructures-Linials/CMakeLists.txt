cmake_minimum_required(VERSION 3.17)
project(ESIN)

set(CMAKE_CXX_STANDARD 11)


include_directories(esin)

add_executable(ESIN test.cpp Graf/graf.h Graf/LlistaIterator.h)


