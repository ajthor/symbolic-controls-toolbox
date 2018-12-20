#ifndef MATH_MATRIX_EXPR_MUL_HPP
#define MATH_MATRIX_EXPR_MUL_HPP

#include "matrix.hpp"
#include "expr.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprMul
//
template<typename T, typename M1, typename M2>
class ExprMul : public Matrix<T, ExprMul<T, M1, M2>> {
private:
  const M1 &lhs_;
  const M2 &rhs_;

public:
  explicit inline ExprMul(const M1 &lhs, const M2 &rhs);
};

template<typename T, typename M1, typename M2>
inline ExprMul<T, M1, M2>::ExprMul(const M1 &lhs,
                                   const M2 &rhs) :
                                   lhs_(lhs),
                                   rhs_(rhs) {
  //
}

template<typename T, typename M>
inline const ExprMul<T, T, M>
operator*(T &scalar, Matrix<T, M> &m) {
  return ExprMul<T, T, M>(scalar, ~m);
}

template<typename T, typename M>
inline const ExprMul<T, T, M>
operator*(Matrix<T, M> &m, T &scalar) {
  return ExprMul<T, T, M>(scalar, ~m);
}

template<typename T, typename M1, typename M2>
inline const ExprMul<T, M1, M2>
operator*(Matrix<T, M1> &m1, Matrix<T, M2> &m2) {
  return ExprMul<T, M1, M2>(~m1, ~m2);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_MUL_HPP */
