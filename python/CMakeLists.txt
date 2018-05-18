# Python Support for Controls Library
#
# Note that to install python support, cmake must have access to a system with
# python already installed.

cmake_minimum_required(VERSION 3.3.2)

project(ctrltbx_matlab)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)
set(CTRLTBX_VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

find_package(ctrllib CONFIG REQUIRED)

find_package(SymEngine CONFIG REQUIRED)

# A list of all source files to be included in the shared library.
set(SRC
  py_wrapper.cc
)

# A list of all header files with C header definitions.
set(HEADERS
  py_wrapper.hpp
)

add_library(pyctrl SHARED ${SRC})

install(TARGETS pyctrl DESTINATION lib)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set_target_properties(pyctrl PROPERTIES COMPILE_FLAGS "-Wconversion -Wno-sign-conversion")
endif()

target_link_libraries(pyctrl ${LIBS})

macro(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
    FOREACH(HEADER ${${HEADER_LIST}})
        STRING(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
        install(FILES ${HEADER} DESTINATION include/ctrllib/${DIR})
    ENDFOREACH(HEADER HEADER_LIST)
endmacro(INSTALL_HEADERS_WITH_DIRECTORY)

INSTALL_HEADERS_WITH_DIRECTORY(HEADERS)
