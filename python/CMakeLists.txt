# Python Support for Controls Library
#
# Note that to install python support, cmake must have access to a system with
# python already installed.

find_package(SymEngine CONFIG REQUIRED)


find_package(PythonLibs REQUIRED)
find_package(PythonInterp REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")
find_package(Cython REQUIRED)

include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${PYTHON_INCLUDE_DIRS})

execute_process(
  COMMAND python -c "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
  OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(SYMENGINE_PATH ${PYTHON_SITE_PACKAGES}/symengine)
set(SYMENGINE_LIB_PATH ${SYMENGINE_PATH}/lib)
set(SYMENGINE_INCLUDE_PATH ${SYMENGINE_PATH}/include)

# A list of all source files to be included in the shared library.
set(SRC
  py_wrapper.cc
)

# A list of all header files with C header definitions.
set(HEADERS
  py_wrapper.hpp
)

add_library(pyctrl_wrapper SHARED ${SRC})

set(CYTHON_INCLUDE_DIRECTORIES ${SYMENGINE_LIB_PATH})
# list(APPEND CYTHON_INCLUDE_DIRECTORIES ${SYMENGINE_LIB_PATH})

cython_compile_pyx(pyctrl ${SYMENGINE_LIB_PATH})

list(APPEND SRC pyctrl.cc)

add_library(pyctrl SHARED pyctrl.cc)
target_include_directories(pyctrl PUBLIC ${SYMENGINE_LIB_PATH})
target_link_libraries(pyctrl ${PYTHON_LIBRARIES})
target_link_libraries(pyctrl pyctrl_wrapper)

install(TARGETS pyctrl DESTINATION lib)

target_link_libraries(pyctrl ${LIBS})

macro(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
    foreach(HEADER ${${HEADER_LIST}})
        string(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
        install(FILES ${HEADER} DESTINATION include/ctrllib/${DIR})
    endforeach(HEADER HEADER_LIST)
endmacro(INSTALL_HEADERS_WITH_DIRECTORY)

INSTALL_HEADERS_WITH_DIRECTORY(HEADERS)
