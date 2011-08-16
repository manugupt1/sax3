#FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.desktop")
#INSTALL(FILES ${files} DESTINATION /usr/share/sax3/modules.d)
install(FILES touchpad.desktop keyboard.desktop mouse.desktop monitor.desktop DESTINATION /usr/share/sax3/modules.d)
