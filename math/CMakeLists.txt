# Source Files for Controls Library

# A list of all source files to be included in the shared library. This should
# point to files with extern "C" function definitions.
set(SRC
  c_wrapper_math.cc
  # math.cc
)

# A list of all header files with C header definitions.
set(HEADERS
  c_wrapper_math.hpp
  math.hpp
  matrix/assert.hpp
  matrix/matrix.hpp
  matrix/dense.hpp
  matrix/vector.hpp
  matrix/symbolic.hpp
  matrix/symbolic_dense.hpp
  matrix/symbolic_vector.hpp
  matrix/expr_add.hpp
  matrix/expr_sub.hpp
  matrix/expr_mul.hpp
  matrix/expr_inverse.hpp
  matrix/expr_transpose.hpp
  matrix/expr_neg.hpp
  matrix/expr_jacobian.hpp
  traits/is_dense_matrix.hpp
  traits/is_expr.hpp
  traits/is_matrix.hpp
  traits/is_symbolic.hpp
  traits/is_vector.hpp
)

INSTALL_HEADERS_WITH_DIRECTORY(HEADERS)

prepend(CURRENT_SRC ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})
prepend(CURRENT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

set(PROJECT_SRC ${PROJECT_SRC} ${CURRENT_SRC} PARENT_SCOPE)
set(PROJECT_HEADERS ${PROJECT_HEADERS} ${CURRENT_HEADERS} PARENT_SCOPE)
