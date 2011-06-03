include_directories(${SaX3_SOURCE_DIR}/src/ui)
link_directories(${SaX3_BINARY_DIR}/src/ui)

include_directories(${LIBYUI_INCLUDE_DIR})

add_library(yui yui.cxx)

target_link_libraries(yui ${LIBYUI_INCLUDE_DIR})
