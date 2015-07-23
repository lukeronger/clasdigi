set(test_names clasdigi-test1 clasdigi-test2 tdc_test1 tdc_test2)

foreach(exename ${test_names})
   add_executable(${exename} ${exename}.cxx)
   target_link_libraries(${exename} ClasDAQ ClasHits)
   install(TARGETS ${exename}
      # IMPORTANT: Add the bar executable to the "export-set"
      RUNTIME DESTINATION "${CMAKE_BINARY_DIR}" COMPONENT bin)
endforeach()


#target_link_libraries(${exename} ClasDAQ ClasHits)
