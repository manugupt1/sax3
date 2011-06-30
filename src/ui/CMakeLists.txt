include_directories(${SaX3_SOURCE_DIR}/src/ui)
link_directories(${SaX3_BINARY_DIR}/src/ui)

include_directories(${LIBYUI_INCLUDE_DIR})

add_library(sax3-yuif SHARED yuifactory.cxx yui.cxx)

install(TARGETS sax3-yuif LIBRARY DESTINATION lib${LIB_SUFFIX})
target_link_libraries(sax3-yuif ${LIBYUI_INCLUDE_DIR})
