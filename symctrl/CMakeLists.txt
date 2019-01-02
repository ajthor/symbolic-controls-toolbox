# Source Files for Controls Library

# A list of all source files to be included in the shared library. This should
# point to files with extern "C" function definitions.
set(SRC
  analysis.cc
  c_wrapper.cc
  controller.cc
  mdp.cc
  state_space.cc
  transfer_function.cc
  visitor.cc
  math/functor/kernel.cc
  math/matrix/operation/gram.cc
  ode/euler.cc
)

# A list of all header files with C header definitions.
set(HEADERS
  assert.hpp
  analysis.hpp
  c_wrapper.hpp
  controller.hpp
  function.hpp
  kernel.hpp
  mdp.hpp
  state_space.hpp
  subs.hpp
  system.hpp
  transfer_function.hpp
  visitor.hpp
  math/math.hpp
  math/functor/functor.hpp
  math/functor/kernel.hpp
  math/functor/lambda.hpp
  math/matrix/block.hpp
  math/matrix/block/block.hpp
  math/matrix/constant.hpp
  math/matrix/constant/identity.hpp
  math/matrix/constant/ones.hpp
  math/matrix/constant/zeros.hpp
  math/matrix/dense.hpp
  math/matrix/dense/dense.hpp
  math/matrix/matrix.hpp
  math/matrix/sparse.hpp
  math/matrix/sparse/sparse.hpp
  math/matrix/static.hpp
  math/matrix/static/static.hpp
  math/matrix/vector.hpp
  math/matrix/vector/vector.hpp
  math/matrix/expression.hpp
  math/matrix/expression/expression.hpp
  math/matrix/expression/matrix.hpp
  math/matrix/expression/symbolic.hpp
  math/matrix/expression/dense.hpp
  math/matrix/expression/vector.hpp
  math/matrix/expression/constant.hpp
  math/matrix/expression/block.hpp
  math/matrix/expression/sparse.hpp
  math/matrix/expression/add.hpp
  math/matrix/expression/sub.hpp
  math/matrix/expression/mul.hpp
  math/matrix/expression/inverse.hpp
  math/matrix/expression/transpose.hpp
  math/matrix/expression/neg.hpp
  math/matrix/operation/gram.hpp
  math/matrix/operation/jacobian.hpp
  math/matrix/operation/norm.hpp
  math/random/random_distribution.hpp
  math/random/random_variable.hpp
  traits/is_constant.hpp
  traits/is_dense.hpp
  traits/is_expr.hpp
  traits/is_matrix.hpp
  traits/is_scalar.hpp
  traits/is_symbolic.hpp
  traits/is_vector.hpp
  ode/ode.hpp
)

INSTALL_HEADERS_WITH_DIRECTORY(HEADERS)

prepend(CURRENT_SRC ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})
prepend(CURRENT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} ${HEADERS})

set(PROJECT_SRC ${PROJECT_SRC} ${CURRENT_SRC} PARENT_SCOPE)
set(PROJECT_HEADERS ${PROJECT_HEADERS} ${CURRENT_HEADERS} PARENT_SCOPE)
