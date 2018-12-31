#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_CONSTANT_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_CONSTANT_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/constant/identity.hpp>
#include <symctrl/math/matrix/constant/ones.hpp>
#include <symctrl/math/matrix/constant/zeros.hpp>
#include <symctrl/math/matrix/expression/unary.hpp>
#include <symctrl/traits/is_scalar.hpp>

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

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_EXPRESSION_CONSTANT_HPP */
