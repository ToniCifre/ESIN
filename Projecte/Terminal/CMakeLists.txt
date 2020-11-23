cmake_minimum_required(VERSION 3.17)
project(ESIN)

set(CMAKE_CXX_STANDARD 11)


INCLUDE_DIRECTORIES(include)
LINK_DIRECTORIES(include)

add_executable(ESIN terminal.cpp)

TARGET_LINK_LIBRARIES(ESIN include/esin/util include/esin/error)




