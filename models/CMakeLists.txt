# Source Files for Controls Library

# A list of all source files to be included in the shared library. This should
# point to files with extern "C" function definitions.
set(SRC
  c_wrapper.cc
  control_model.cc
  system.cc
  state_space.cc
  transfer_function.cc
)

# SET_SOURCE_FILES_PROPERTIES(${SRC} PROPERTIES LANGUAGE CXX)

# A list of all header files with C header definitions.
set(HEADERS
  c_wrapper.hpp
  control_model.hpp
  system.hpp
  state_space.hpp
  transfer_function.hpp
)

add_library(ctrl SHARED ${SRC})

install(TARGETS ctrl DESTINATION lib)

target_link_libraries(ctrl ${LIBS})

macro(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
    FOREACH(HEADER ${${HEADER_LIST}})
        STRING(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
        install(FILES ${HEADER} DESTINATION include/libctrl/${DIR})
    ENDFOREACH(HEADER HEADER_LIST)
endmacro(INSTALL_HEADERS_WITH_DIRECTORY)

INSTALL_HEADERS_WITH_DIRECTORY(HEADERS)
