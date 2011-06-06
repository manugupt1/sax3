#file(MAKE_DIRECTORY /usr/share/sax3/res)
#file(COPY . DESTINATION /usr/share/sax3/res PATTERN "*.png" PATTERN "*.txt" EXCLUDE)

#add_custom_target(manu 	SOURCES PATTERN *.png)

function    (cm_export_file FILE DEST)
  if    (NOT TARGET export-files)
    add_custom_target(export-files ALL COMMENT "Exporting files into build tree")
  endif (NOT TARGET export-files)
  get_filename_component(FILENAME "${FILE}" NAME)
  add_custom_command(TARGET export-files COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/${FILE}" "${CMAKE_CURRENT_BINARY_DIR}/${DEST}/${FILENAME}")
  install(FILES "${FILE}" DESTINATION "${DEST}")
endfunction (cm_export_file)


INSTALL(FILES mouse.png keyboard.png monitor.png touchpad.png DESTINATION /usr/share/sax3/res)

#cm_export_file("mouse.png" "usr/share/sax3/res")
