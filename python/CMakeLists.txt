# Python Support for Controls Library
#
# Note that to install python support, cmake must have access to a system with
# python already installed.

find_package(SymEngine CONFIG REQUIRED)

find_package(PythonLibs REQUIRED)
find_package(PythonInterp REQUIRED)

find_package(Cython REQUIRED)
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${PYTHON_INCLUDE_DIRS})

# A list of all source files to be included in the shared library.
set(SRC
  py_wrapper.cc
)

# A list of all header files with C header definitions.
set(HEADERS
  py_wrapper.hpp
)

add_cython_target(pyctrl CXX py_wrapper.pyx)
add_library(pyctrl SHARED ${SRC})

target_link_libraries(pyctrl ${PYTHON_LIBRARIES})

install(TARGETS pyctrl DESTINATION lib)

target_link_libraries(pyctrl ${LIBS})

macro(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
    FOREACH(HEADER ${${HEADER_LIST}})
        STRING(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
        install(FILES ${HEADER} DESTINATION include/ctrllib/${DIR})
    ENDFOREACH(HEADER HEADER_LIST)
endmacro(INSTALL_HEADERS_WITH_DIRECTORY)

INSTALL_HEADERS_WITH_DIRECTORY(HEADERS)
