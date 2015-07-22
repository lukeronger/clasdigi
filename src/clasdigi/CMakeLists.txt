set(exename clasdigi)
add_executable(${exename} ${exename}.cxx)

target_link_libraries(${exename} ClasDAQ ClasHits)

install(TARGETS ${exename}
  # IMPORTANT: Add the bar executable to the "export-set"
  EXPORT ${PROJECT_NAME}Targets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)
