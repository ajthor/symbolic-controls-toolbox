#ifndef MATH_MATRIX_EXPR_MUL_HPP
#define MATH_MATRIX_EXPR_MUL_HPP

#include "matrix.hpp"
#include "expr.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprMul
//
template<typename M1, typename M2>
class ExprMul : public Expression<Matrix<ExprMul<M1, M2>>> {
private:
  const M1 &lhs_;
  const M2 &rhs_;

public:
  explicit inline ExprMul(const M1 &lhs, const M2 &rhs);

  template<typename DT>
  friend inline void apply_(Matrix<DT> &lhs,
                            const ExprMul<M1, M2> &rhs) {
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void apply_add_(Matrix<DT> &lhs,
                                const ExprMul<M1, M2> &rhs) {
    apply_add_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }
};

template<typename M1, typename M2>
inline ExprMul<M1, M2>::ExprMul(const M1 &lhs,
                                const M2 &rhs) :
                                lhs_(lhs),
                                rhs_(rhs) {
  //
}

// template<typename T, typename M>
// inline const ExprMul<T, T, M>
// operator*(T &scalar, Matrix<M> &m) {
//   return ExprMul<T, T, M>(scalar, ~m);
// }
//
// template<typename T, typename M>
// inline const ExprMul<M, T>
// operator*(Matrix<M> &m, T &scalar) {
//   return ExprMul<M, T>(scalar, ~m);
// }

template<typename M1, typename M2>
inline const ExprMul<M1, M2>
operator*(const Matrix<M1> &m1, const Matrix<M2> &m2) {
  return ExprMul<M1, M2>(~m1, ~m2);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_MUL_HPP */
