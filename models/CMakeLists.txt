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

# A list of all header files with C header definitions.
set(HEADERS
  c_wrapper.hpp
  control_model.hpp
  system.hpp
  state_space.hpp
  transfer_function.hpp
)

INSTALL_HEADERS_WITH_DIRECTORY(HEADERS)

# set(PROJECT_SRC ${SRC} PARENT_SCOPE)
# set(PROJECT_HEADERS ${HEADERS} PARENT_SCOPE)

prepend(PROJECT_SRC ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})
prepend(PROJECT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

set(PROJECT_SRC ${PROJECT_SRC} PARENT_SCOPE)
set(PROJECT_HEADERS ${PROJECT_HEADERS} PARENT_SCOPE)
