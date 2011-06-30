include_directories(${SaX3_SOURCE_DIR}/src)
link_directories(${SaX3_BINARY_DIR}/src)

include_directories(${LIBYUI_INCLUDE_DIR})

add_subdirectory(ui)
add_subdirectory(res)
add_subdirectory(modules.d)
add_subdirectory(lens)

add_executable(sax3 main.cxx)
add_executable(sax3-keyboard keyboard.cxx)
#install(PROGRAMS sax3 sax3-keyboard DESTINATION sbin)
message("manu = ${CMAKE_CURRENT_BINARY_DIR}")
#FILE(GLOB execs "${CMAKE_CURRENT_BINARY_DIR}/src/sax3*")
install(PROGRAMS sax3 sax3-keyboard DESTINATION sbin)
target_link_libraries(sax3 sax3-yuif ${LIBYUI_LIBRARY} augeas)
target_link_libraries(sax3-keyboard sax3-yuif ${LIBYUI_LIBRARY} augeas)
