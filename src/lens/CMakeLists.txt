FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.aug")
INSTALL(FILES ${files} DESTINATION /usr/share/libaugeas0/augeas/lenses/dist)
INSTALL(FILES ${files} DESTINATION /usr/share/augeas/lenses/dist)
