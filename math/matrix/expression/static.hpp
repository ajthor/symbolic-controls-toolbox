#ifndef MATH_MATRIX_EXPRESSION_CONSTANT_HPP
#define MATH_MATRIX_EXPRESSION_CONSTANT_HPP

#include <math/assert.hpp>
#include <math/matrix/constant/identity.hpp>
#include <math/matrix/constant/ones.hpp>
#include <math/matrix/constant/zeros.hpp>
#include <math/matrix/expression/unary.hpp>
#include <math/traits/is_scalar.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// StaticMatrix Equal
//
template<typename T, size_t N, size_t M>
inline bool equal(const StaticMatrix<T, N, M> &lhs, const StaticMatrix<T, N, M> &rhs) {
  for(size_t i = 0; i < N; i++) {
    for(size_t j = 0; j < M; j++) {
      if(!equal((~lhs)(i, j), (~rhs)(i, j)))
        return false;
    }
  }

  return true;
}


} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPRESSION_CONSTANT_HPP */
