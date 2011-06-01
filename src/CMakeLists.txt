include_directories(${SaX3_SOURCE_DIR}/src)
link_directories(${SaX3_BINARY_DIR}/src)

include_directories(${LIBYUI_INCLUDE_DIR})

set(CMAKE_INSTALL_PREFIX "/home/hawk/sax3")

add_subdirectory(ui)
add_subdirectory(res)
add_executable(main main.cxx)

target_link_libraries(main ui ${LIBYUI_LIBRARY})
