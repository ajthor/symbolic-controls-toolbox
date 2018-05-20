# FindCython CMake module.
#
# Loads Cython and implements several functions for working with Cython modules.

SET(CYTHON_BIN cython CACHE STRING "cython binary")
SET(CYTHON_FLAGS --cplus --fast-fail)

# Load Cython
find_program(CYTHON_EXECUTABLE NAMES ${CYTHON_BIN})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Cython REQUIRED_VARS CYTHON_EXECUTABLE)

mark_as_advanced(CYTHON_EXECUTABLE)

set(CYTHON_CXX_EXTENSION "cc")
set(CYTHON_C_EXTENSION "c")

if(NOT CYTHON_INCLUDE_DIRECTORIES)
  set(CYTHON_INCLUDE_DIRECTORIES .)
endif(NOT CYTHON_INCLUDE_DIRECTORIES)

macro(CYTHON_COMPILE_PYX name)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${name}.pxd)
    set(DEPENDS ${name}.pyx ${name}.pxd)
  else(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${name}.pxd)
    set(DEPENDS ${name}.pyx)
  endif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${name}.pxd)

  set(DEPENDS ${DEPENDS} ${ARGN})

  add_custom_command(
    OUTPUT ${name}.cc
    COMMAND ${CYTHON_BIN}
    ARGS ${CYTHON_FLAGS} -I ${CYTHON_INCLUDE_DIRECTORIES} -o ${name}.${CYTHON_CXX_EXTENSION} ${CMAKE_CURRENT_SOURCE_DIR}/${name}.pyx
    DEPENDS ${DEPENDS}
    COMMENT "Cythonizing ${name}.pyx"
  )
endmacro()
