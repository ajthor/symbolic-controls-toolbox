# FindCython CMake module.
#
# Loads Cython and implements several functions for working with Cython modules.

set(CYTHON_BIN cython CACHE STRING "cython binary")
set(CYTHON_FLAGS --cplus --fast-fail)

# Load Cython
find_program(CYTHON_EXECUTABLE NAMES ${CYTHON_BIN})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Cython REQUIRED_VARS CYTHON_EXECUTABLE)

mark_as_advanced(CYTHON_EXECUTABLE)

set(CYTHON_CXX_EXTENSION "cc")
set(CYTHON_C_EXTENSION "c")

if(NOT CYTHON_INCLUDE_DIRECTORIES)
  set(CYTHON_INCLUDE_DIRECTORIES .)
endif(NOT CYTHON_INCLUDE_DIRECTORIES)

macro(CYTHON_COMPILE_PYX FILE_NAME)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}.pxd)
    set(DEPENDS ${FILE_NAME}.pyx ${FILE_NAME}.pxd)
  else(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}.pxd)
    set(DEPENDS ${FILE_NAME}.pyx)
  endif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}.pxd)

  set(DEPENDS ${DEPENDS} ${ARGN})

  add_custom_command(
    OUTPUT ${FILE_NAME}.cc
    COMMAND ${CYTHON_EXECUTABLE}
    ARGS ${CYTHON_FLAGS} -I ${CYTHON_INCLUDE_DIRECTORIES} -o ${FILE_NAME}.${CYTHON_CXX_EXTENSION} ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}.pyx
    DEPENDS ${DEPENDS}
    COMMENT "Cythonizing ${FILE_NAME}.pyx"
  )
endmacro()
