cmake_minimum_required(VERSION 2.8)
project(SaX3)

find_package(Libyui)
set(CMAKE_CXX_FLAGS "-Wall -pedantic -laugeas")
#install(FILES COPYING.GPL-3.0 DESTINATION /usr/share/ax3/)
add_subdirectory(src)
