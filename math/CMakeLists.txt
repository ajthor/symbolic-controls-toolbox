# Source Files for Controls Library

# A list of all source files to be included in the shared library. This should
# point to files with extern "C" function definitions.
set(SRC
  c_wrapper_math.cc
  # visitor.cc
)

# A list of all header files with C header definitions.
set(HEADERS
  c_wrapper_math.hpp
  math.hpp
  assert.hpp
  matrix/matrix.hpp
  matrix/dense.hpp
  matrix/dense/dense.hpp
  matrix/vector.hpp
  matrix/vector/vector.hpp
  matrix/static.hpp
  matrix/static/static.hpp
  matrix/constant.hpp
  matrix/constant/identity.hpp
  matrix/constant/ones.hpp
  matrix/constant/zeros.hpp
  matrix/block.hpp
  matrix/block/block.hpp
  matrix/sparse.hpp
  matrix/sparse/sparse.hpp
  matrix/expression.hpp
  matrix/expression/expression.hpp
  matrix/expression/matrix.hpp
  matrix/expression/symbolic.hpp
  matrix/expression/dense.hpp
  matrix/expression/vector.hpp
  matrix/expression/constant.hpp
  matrix/expression/block.hpp
  matrix/expression/sparse.hpp
  matrix/expression/add.hpp
  matrix/expression/sub.hpp
  matrix/expression/mul.hpp
  matrix/expression/inverse.hpp
  matrix/expression/transpose.hpp
  matrix/expression/neg.hpp
  matrix/operation/jacobian.hpp
  matrix/operation/norm.hpp
  traits/is_dense.hpp
  traits/is_expr.hpp
  traits/is_matrix.hpp
  traits/is_scalar.hpp
  traits/is_static.hpp
  traits/is_symbolic.hpp
  traits/is_vector.hpp
  # matrix/visitor.hpp
)

INSTALL_HEADERS_WITH_DIRECTORY(HEADERS)

prepend(CURRENT_SRC ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})
prepend(CURRENT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

set(PROJECT_SRC ${PROJECT_SRC} ${CURRENT_SRC} PARENT_SCOPE)
set(PROJECT_HEADERS ${PROJECT_HEADERS} ${CURRENT_HEADERS} PARENT_SCOPE)
