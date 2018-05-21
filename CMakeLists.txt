# Controls Library

cmake_minimum_required(VERSION 3.3.2)

project(ctrllib)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)
set(CTRLLIB_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

# set_target_properties(ctrllib PROPERTIES VERSION ${CTRLLIB_VERSION})

find_package(SymEngine CONFIG REQUIRED)

include(ExternalProject)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

# Macro to install header files to the include directory.
macro(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
    foreach(HEADER ${${HEADER_LIST}})
        string(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})

        install(FILES 
          ${HEADER}
          DESTINATION include/libctrl/${DIR}
        )

    endforeach()
endmacro()

# Macro to prepend a string to each element of a list.
macro(PREPEND NEW_VAR PREFIX)
  set(NEW_LIST "")

  foreach(FILE_NAME ${ARGN})
    list(APPEND NEW_LIST "${PREFIX}/${FILE_NAME}")
  endforeach()

  set(${NEW_VAR} "${NEW_LIST}")

endmacro()

# List of project subdirectories to be added.
# When modifying this file with new subdirectories, edit this variable.
# The order of the subdirectories is the order the directories will be added.
set(PROJECT_DIRECTORIES
  models
)

# Prepend the project source directory.
prepend(ABS_PROJECT_DIRECTORIES ${PROJECT_DIRECTORIES} ${PROJECT_SOURCE_DIR})

include_directories("${ABS_PROJECT_DIRECTORIES}")

# Add all subdirectories.
foreach(dir ${PROJECT_DIRECTORIES})
  add_subdirectory(models)
endforeach()


# if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#   add_library(${name} MODULE ${ARGN})
#
#   set_target_properties(${name} PROPERTIES
#     LINK_FLAGS "-flat_namespace -undefined suppress")
#
# else()
#   add_library(${name} SHARED ${ARGN})
#
# endif()
add_library(ctrl SHARED ${PROJECT_SRC})
# target_link_libraries(ctrl ${LIBS})

install(TARGETS ctrl DESTINATION lib)

# Matlab Support
option(BUILD_MATLAB "Build Matlab MEX files." OFF)

# Python Support
option(BUILD_PYTHON "Build Python wrapper library." OFF)

if(BUILD_MATLAB)
  add_subdirectory(matlab)
  # ExternalProject_Add(ctrltbx_matlab
  #   SOURCE_DIR "${PROJECT_SOURCE_DIR}/matlab"
  #   BUILD_COMMAND make
  #   INSTALL_COMMAND make install
  #   BUILD_ALWAYS 1
  # )
endif()

if(BUILD_PYTHON)
  add_subdirectory(python)
  # ExternalProject_Add(ctrltbx_matlab
  #   SOURCE_DIR "${PROJECT_SOURCE_DIR}/python"
  #   BUILD_COMMAND make
  #   INSTALL_COMMAND make install
  #   BUILD_ALWAYS 1
  # )
endif()
