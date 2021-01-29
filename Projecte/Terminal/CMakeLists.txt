cmake_minimum_required(VERSION 3.17)

project(Terminal)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/incl)

add_executable(Terminal driver_gestterm.cpp
        contenidor.cpp contenidor.hpp
        ubicacio.cpp ubicacio.hpp
        terminal.cpp terminal.hpp
        cataleg.hpp)

target_link_libraries(Terminal ${CMAKE_SOURCE_DIR}/lib/libesin.so)