set(exename clasdigi)

add_executable(${exename} ${exename}.cxx)
target_link_libraries(${exename} ClasDAQ ClasHits ClasSigs ClasSim)
install(TARGETS ${exename}
  # IMPORTANT: Add the bar executable to the "export-set"
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)


set(more_names clasdigi_HTCC clasdigi_output_format)

foreach(exename ${more_names})
   add_executable(${exename} ${exename}.cxx)
   target_link_libraries(${exename} ClasDAQ ClasHits ClasSigs ClasSim)
   install(TARGETS ${exename}
     # IMPORTANT: Add the bar executable to the "export-set"
     EXPORT ${PROJECT_NAME}Targets
     RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
endforeach()
