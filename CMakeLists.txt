cmake_minimum_required(VERSION 3.25)
project(bank)

set(CMAKE_CXX_STANDARD 11)

add_executable(bank main.cpp account.cpp account.h system.cpp system.h)
