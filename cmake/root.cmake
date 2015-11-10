## Override root's ROOT_GENERATE_DICTIONARY macro to be less error-prone. This
## is done by only allowing for explicitly speficied header locations/include
## directories, instead of using the full search path for this module.
function(ROOT_GENERATE_DICTIONARY dictionary)
  CMAKE_PARSE_ARGUMENTS(ARG "" "" "LINKDEF;OPTIONS" "" ${ARGN})
  ## find and call ROOTCLING
  find_program(ROOTCLING rootcling)
  add_custom_command(
    OUTPUT ${dictionary}.cxx ${dictionary}_rdict.pcm 
    COMMAND ${ROOTCLING} -f ${dictionary}.cxx -s ${dictionary}.pcm 
            ${ARG_OPTIONS} ${ARG_UNPARSED_ARGUMENTS} ${ARG_LINKDEF}
    DEPENDS ${includes} ${linkdefs})
endfunction()
