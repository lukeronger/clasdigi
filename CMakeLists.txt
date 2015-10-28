#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ClasDigi CXX C Fortran)

set(ClasDigi_LIB_NAMES
   Hits
   DAQ
   Sigs
   Sim
   Geo
   Kine
   Mag
   )

set(ClasDigi_EXE_NAMES
   clasdigi
   tests
   )

# The version number.
set(ClasDigi_MAJOR_VERSION 0)
set(ClasDigi_MINOR_VERSION 1)
set(ClasDigi_PATCH_VERSION 0)
SET(ClasDigi_VERSION "${ClasDigi_MAJOR_VERSION}.${ClasDigi_MINOR_VERSION}.${ClasDigi_PATCH_VERSION}")

# ---------------------------------------------------------------------------
# Configure the find_package outputs for this library
# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
   set(DEF_INSTALL_CMAKE_DIR CMake)
else()
   set(DEF_INSTALL_CMAKE_DIR lib/${PROJECT_NAME})
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

#MESSAGE("installprefix : ${CMAKE_INSTALL_PREFIX}")
if(NOT CMAKE_INSTALL_PREFIX)
   SET(ClasDigi_PREFIX "/usr/local")
else() 
   SET(ClasDigi_PREFIX ${CMAKE_INSTALL_PREFIX})
endif()

# ---------------------------------------------------------------------------
#
set(ClasDigi_CXX_CFLAGS)
set(ClasDigi_CXX_LDFLAGS)
set(ClasDigi_CXX_LIBS)
set(ClasDigi_CXX_INC_DIR)
set(ClasDigi_FC_CFLAGS)
set(ClasDigi_DATA_DIR $ENV{JLAB_ROOT}/noarch/data)
set(ClasDigi_PREFIX)

set(ClasDigi_CXX_LIBS      "-L${CMAKE_INSTALL_PREFIX}/lib ")
set(ClasDigi_CXX_LDFLAGS   "${ClasDigi_CXX_LDFLAGS} ${CMAKE_SHARED_LINKER_FLAGS}")
set(ClasDigi_CXX_INC_DIR   "-I${CMAKE_INSTALL_PREFIX}/include/ClasDigi ")

#set (ClasDigi_COMPILER_FLAGS "-Wall")
set(ClasDigi_COMPILER_FLAGS   "-Wno-unused-variable -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS         "-std=c++14 ${CMAKE_CXX_FLAGS} ${ClasDigi_COMPILER_FLAGS} ")

set(ClasDigi_PDF_GRID_DIR     "${PROJECT_SOURCE_DIR}/main/grid")
set(ClasDigi_GRID_DATA_DIR    "${ClasDigi_GRID_DATA_DIR} ${ClasDigi_PDF_GRID_DIR}")
set(CMAKE_USE_ROOT6        ON)
set(PROJECT_USE_ROOT6      ${CMAKE_USE_ROOT6})

#-------------------------------------------------------
set(CMAKE_MODULE_PATH
   ${CMAKE_MODULE_PATH}
   ${PROJECT_SOURCE_DIR}/cmake
   ${PROJECT_SOURCE_DIR}/cmake/Modules 
   )

# ---------------------------------------------------------------------------
# Must be out of source build
macro(ClasDigi_CHECK_OUT_OF_SOURCE_BUILD)
   get_filename_component(bindir_parent ${CMAKE_BINARY_DIR} PATH)
   if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
      file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/Testing)
      file(REMOVE ${CMAKE_SOURCE_DIR}/DartConfiguration.tcl)
      message(FATAL_ERROR "ClasDigi should be built as an out of source build, to keep the source directory clean. Please create a extra build directory and run the command 'cmake <path_to_source_dir>' in this newly created directory.  You have also to delete the directory CMakeFiles and the file CMakeCache.txt in the source directory. Otherwise cmake will complain even if you run it from an out-of-source directory.")
   elseif(IS_SYMLINK ${CMAKE_BINARY_DIR} AND CMAKE_SOURCE_DIR STREQUAL bindir_parent)
      message(FATAL_ERROR "ClasDigi cannot be built from a sub-directory of the source tree that is a symlink. This is a current limitation of CMake. Please create a real build directory and run the command 'cmake <path_to_source_dir>' in this newly created directory.")
   endif()
endmacro()
# NOTE: Doesn't work with older cmake versions:
ClasDigi_CHECK_OUT_OF_SOURCE_BUILD()

# Check the compiler and set the compile and link flags
#set(CMAKE_BUILD_TYPE Debug)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

#----------------------------------------------------------------------------
# Find Libraries
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist MathMore Graf Graf3d
   Gpad GX11 GeomPainter X3d Gviz3d RGL
   Eve EG Foam GenVector Geom GLEW Gui HistPainter MathCore Matrix MLP Net
   Physics Spectrum Thread Tree TreeViewer)
include(${ROOT_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})
message("ROOT_CXX_FLAGS : ${ROOT_CXX_FLAGS}")
add_definitions(${ROOT_CXX_FLAGS})
set(LINK_DIRECTORIES
   ${ROOT_LIBRARY_DIR}
   )
set(LINK_LIBRARIES 
   ${LINK_LIBRARIES}
   ${ROOT_LIBRARIES}
   )

# ----------
# CLHEP
#set (CLHEP_CONFIG_DEBUG 1)
find_package(CLHEP  REQUIRED)
#  CLHEP_INCLUDE_DIRS - include directories for CLHEP
#  CLHEP_DEFINITIONS  - compile definitions needed to use CLHEP
#  CLHEP_LIBRARIES    - libraries to link against
set(CLHEP_LIBRARY_DIR $ENV{JLAB_PREFIX}/lib)
include_directories(${CLHEP_INCLUDE_DIR})
#message(" CLHEP_DEFINITIONS = ${CLHEP_DEFINITIONS} " )

# EVIO
#set(EVIO_INCLUDE_DIR $ENV{JLAB_PREFIX}/include)
#set(EVIO_LIBRARY_DIR $ENV{JLAB_PREFIX}/lib)
#set(EVIO_LIBRARIES  evio evioxx expat)

set(LINK_DIRECTORIES
   ${LINK_DIRECTORIES}
   ${EVIO_LIBRARY_DIR}
   ${CLHEP_LIBRARY_DIR}
   ${ROOT_LIBRARY_DIR}
   )
set(LINK_LIBRARIES 
   ${LINK_LIBRARIES}
   ${ROOT_LIBRARIES}
   ${EVIO_LIBRARIES}
   ${CLHEP_LIBRARIES}
   )

link_directories(${LINK_DIRECTORIES})


include_directories(
   ${ROOT_INCLUDE_DIR}
   ${CMAKE_BINARY_DIR}
   ${EVIO_INCLUDE_DIR}
   ${CLHEP_INCLUDE_DIR}
   ${INCLUDE_DIRECTORIES}
   )


#----------------------------------------------------------------------------
# not sure this is the best way to do this....
set(ClasDigi_FC_CFLAGS "${ClasDigi_FC_CFLAGS} ${CMAKE_Fortran_FLAGS}")
#set(CMAKE_Fortran_FLAGS " -D\"ClasDigi_PDF_GRID_DIR='${ClasDigi_PDF_GRID_DIR}'\" -g -O2 -Wall -fPIC -Iinclude -ffixed-line-length-none -x f77-cpp-input ")
set(CMAKE_Fortran_FLAGS " -D\"ClasDigi_PDF_GRID_DIR='${ClasDigi_PDF_GRID_DIR}'\" -g -O2 -Wall  -ffixed-line-length-none -x f77-cpp-input ")
set(CMAKE_Fortran_FLAGS_RELEASE "${CMAKE_Fortran_FLAGS}")


set(CMAKE_Fortran_FLAGS " -D\"ClasDigi_PDF_GRID_DIR='${ClasDigi_PDF_GRID_DIR}'\" -g -O2 -Wall  -ffixed-line-length-none -x f77-cpp-input ")
set(ClasDigi_CXX_LDFLAGS   "${ClasDigi_CXX_LDFLAGS} ${CMAKE_SHARED_LINKER_FLAGS}")

# ---------------------------------------
set(ClasDigi_SHARED_LIB_NAMES)
foreach(aSharedLib ${ClasDigi_LIB_NAMES})
   set(ClasDigi_CXX_LIBS      "${ClasDigi_CXX_LIBS} -lClas${aSharedLib} ")
   set(ClasDigi_SHARED_LIB_NAMES    ${ClasDigi_SHARED_LIB_NAMES} Clas${aSharedLib})
endforeach(aSharedLib)

# configure a header file to pass some of the CMake settings to the source code
configure_file (
   "${PROJECT_SOURCE_DIR}/ClasDigiConfig.h.in"
   "${PROJECT_BINARY_DIR}/ClasDigiConfig.h"
   )

#----------------------------------------------------------------------------
# Add the executable
#add_executable(ClasDigi-config ClasDigi-config.cxx )
add_subdirectory(config)

set(ClasDigi_SHARED_LIBS)
set(ClasDigi_LIBRARIES)
set(ClasDigi_ROOT_DICTS)
set(ClasDigi_PCM_FILES)

# ---------------------------------------
foreach(aSharedLib ${ClasDigi_LIB_NAMES})
   set(ClasDigi_LIBRARIES ${ClasDigi_LIBRARIES} Clas${aSharedLib})
   #set(ClasDigi_SHARED_LIBS ${ClasDigi_SHARED_LIBS} "${CMAKE_BINARY_DIR}/lib/ClasDigi${aSharedLib}.so")
   set(ClasDigi_ROOT_DICTS ${ClasDigi_ROOT_DICTS} "ClasDigi${aSharedLib}Dict.h")
   set(ClasDigi_ROOT_DICT_SRCS ${ClasDigi_ROOT_DICT_SRCS} "ClasDigi${aSharedLib}Dict.cxx")
   if(CMAKE_USE_ROOT6)
       set(ClasDigi_PCM_FILES ${ClasDigi_PCM_FILES} "ClasDigi${aSharedLib}Dict_rdict.pcm")
   endif(CMAKE_USE_ROOT6)
   if(NOT CMAKE_USE_ROOT6)
       set(ClasDigi_ROOT_DICT_HEADERS ${ClasDigi_ROOT_DICT_HEADERS} "ClasDigi${aSharedLib}Dict.h")
   endif(NOT CMAKE_USE_ROOT6)
   include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/${aSharedLib}/include)
endforeach(aSharedLib)

#ADD_CUSTOM_TARGET(ROOTDICTS DEPENDS ${ClasDigi_ROOT_DICT_SRCS} ${ClasDigi_ROOT_DICT_HEADERS})

foreach(aSharedLib ${ClasDigi_LIB_NAMES})
   #include(${aSharedLib})
   add_subdirectory("src/${aSharedLib}")
endforeach(aSharedLib)

foreach(anExeName ${ClasDigi_EXE_NAMES})
   #include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/${anExeName}/include)
   add_subdirectory("src/${anExeName}")
endforeach(anExeName)

FILE(GLOB GENERATED_HEADERS 
   "${CMAKE_CURRENT_SOURCE_DIR}/*.h" 
   "${PROJECT_BINARY_DIR}/ClasDigiConfig.h")
FILE(GLOB PCM_FILES "${PROJECT_BINARY_DIR}/*.pcm")

# -----------------------------------------------------------
# Set the library version in the main CMakeLists.txt
SET(ClasDigi_LIBRARY_PROPERTIES ${ClasDigi_LIBRARY_PROPERTIES}
    VERSION "${ClasDigi_VERSION}"
    SOVERSION "${ClasDigi_MAJOR_VERSION}"
    SUFFIX ".so"
)

set(ClasDigi_SRCS
   ${Cluster_SRCS}
   ${Cut_SRCS}
   ${Event_SRCS}
   ${General_SRCS}
   ${Geo_SRCS}
   ${Math_SRCS}
   ${Neural_SRCS}
   ${Physics_SRCS}
   ${Physics2_SRCS}
   )
set_source_files_properties(
   ${ClasDigi_SRCS}
   PROPERTIES COMPILE_FLAGS "")
#   PROPERTIES COMPILE_FLAGS "-Wall  -Wextra -Wcomment ")

#add_library(ClasDigi SHARED ${ClasDigi_SRCS})
#target_link_libraries(ClasDigi ${ROOT_LIBRARIES})
#add_dependencies(ClasDigi ROOTDICTS)
#set_target_properties(ClasDigi PROPERTIES ${ClasDigi_LIBRARY_PROPERTIES})

# ------------------------------------------------------------------------------
# Install the libraries 
#foreach(aLib ${ClasDigi_LIB_NAMES})
#   install(TARGETS "ClasDigi${aLib}" DESTINATION   lib)
#endforeach(aLib)

# ------------------------------------------------------------------------------
# Build the binary 
#install(TARGETS ClasDigi DESTINATION lib)
INSTALL(FILES ${files} DESTINATION include/ClasDigi)
install(FILES ${PCM_FILES} DESTINATION lib)
#install(TARGETS ClasDigi-config DESTINATION bin)


# ----------------------------------------------------------------------------
# The cmake stuff goes here

# Add all targets to the build-tree export set
#export(TARGETS ClasDigi FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")
# TODO: replace "ClasDigi" with smaller libraries

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE ${PROJECT_NAME})

set(CONF_LIBRARIES 
   ${ClasDigi_SHARED_LIB_NAMES}  # TODO: Break big library into smaller ones
   )

set(CONF_EXECUTABLES 
   clasdigi-config
   )

set(CONF_INCLUDE_DIRS 
   ${CMAKE_INSTALL_PREFIX}/include
   ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}
   )

set(CONF_LIBRARY_DIRS 
   ${CMAKE_INSTALL_PREFIX}/lib
   )

configure_file(${PROJECT_NAME}Config.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}Config.cmake" @ONLY)
configure_file(${PROJECT_NAME}ConfigVersion.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}ConfigVersion.cmake" @ONLY)

# Install the FooBarConfig.cmake and FooBarConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}Config.cmake"
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT ${PROJECT_NAME}Targets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)


MESSAGE("          ClasDigi_CXX_LIBS: ${ClasDigi_CXX_LIBS}")
MESSAGE("       ClasDigi_CXX_LDFLAGS: ${ClasDigi_CXX_LDFLAGS}")
MESSAGE("       ClasDigi_CXX_INC_DIR: ${ClasDigi_CXX_INC_DIR}")
MESSAGE("             CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
MESSAGE("              FC_COMPILER: ${CMAKE_FC_COMPILER}")
MESSAGE("      CMAKE_Fortran_FLAGS: ${CMAKE_Fortran_FLAGS}")
MESSAGE("                CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
MESSAGE("         CMAKE_LINK_FLAGS: ${CMAKE_LINK_FLAGS}")
MESSAGE("CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")

