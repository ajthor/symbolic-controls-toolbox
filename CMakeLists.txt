# Controls Library

cmake_minimum_required(VERSION 3.3.2)

project(ctrllib)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)
set(CTRLLIB_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

# set_target_properties(ctrllib PROPERTIES VERSION ${CTRLLIB_VERSION})

find_package(SymEngine CONFIG REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

add_subdirectory(src)

# install(TARGETS test DESTINATION lib)
# install(FILES test.h DESTINATION include)


# Matlab Support
option(BUILD_MATLAB "Build Matlab MEX files." OFF)

if(BUILD_MATLAB)
  include(ExternalProject)

  ExternalProject_Add(ctrltbx_matlab
    SOURCE_DIR "${PROJECT_SOURCE_DIR}/matlab"
    BUILD_COMMAND make
    INSTALL_COMMAND make install
    BUILD_ALWAYS 1
  )
endif()
