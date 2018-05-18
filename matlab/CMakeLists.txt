# Matlab Support for Controls Library
#
# Note that to install Matlab support, cmake must have access to a system with
# Matlab already installed.

cmake_minimum_required(VERSION 3.3.2)

project(ctrltbx_matlab)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)
set(CTRLTBX_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

find_package(ctrllib CONFIG REQUIRED
  NO_CMAKE_SYSTEM_PATH
  NO_SYSTEM_ENVIRONMENT_PATH
)

find_package(SymEngine CONFIG REQUIRED)

find_package(Matlab MODULE REQUIRED
  COMPONENTS MAIN_PROGRAM MEX_COMPILER MX_LIBRARY
)

set(MATLAB_MINIMUM_VERSION 9.2)
set(MATLAB_MINIMUM_VERSION_NAME matlab_get_release_name_from_version())

if(Matlab_VERSION_STRING VERSION_LESS ${MATLAB_MINIMUM_VERSION})
  message(FATAL_ERROR "Matlab ${MATLAB_MINIMUM_VERSION_NAME} or greater is required.")
endif()

install(FILES loadlibcontrols.m DESTINATION share/matlab)

set(SRC
  matlab_wrapper.cc
)

matlab_add_mex(NAME matlab_wrapper SHARED SRC ${SRC})
