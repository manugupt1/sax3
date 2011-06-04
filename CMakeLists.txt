cmake_minimum_required(VERSION 2.8)
project(SaX3)

find_package(Libyui)
set(CMAKE_CXX_FLAGS "-Wall -pedantic")
add_subdirectory(src)
