include_directories(${SaX3_SOURCE_DIR}/src)
link_directories(${SaX3_BINARY_DIR}/src)

include_directories(${LIBYUI_INCLUDE_DIR})

add_subdirectory(ui)
add_subdirectory(res)
add_subdirectory(modules.d)
add_subdirectory(lens)

add_executable(main main.cxx)
add_executable(keyboard keyboard.cxx)

target_link_libraries(main yui yuif ${LIBYUI_LIBRARY})
target_link_libraries(keyboard yui yuif ${LIBYUI_LIBRARY})
