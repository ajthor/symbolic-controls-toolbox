#ifndef MATH_MATRIX_EXPR_ADD_HPP
#define MATH_MATRIX_EXPR_ADD_HPP

#include "matrix.hpp"
#include "expr.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprAdd
//
template<typename M1, typename M2>
class ExprAdd : public Expression<Matrix<ExprAdd<M1, M2>>> {
private:
  const M1 &lhs_;
  const M2 &rhs_;

public:
  explicit inline ExprAdd(const M1 &lhs, const M2 &rhs);

  template<typename DT>
  friend inline void apply_(Matrix<DT> &lhs,
                            const ExprAdd<M1, M2> &rhs) {
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void apply_add_(Matrix<DT> &lhs,
                                const ExprAdd<M1, M2> &rhs) {
    apply_add_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  // template<typename DT>
  // friend inline void apply_mul_(Matrix<DT> &lhs,
  //                               const ExprAdd<M1, M2> &rhs) {
  //   apply_add_(~lhs, rhs.lhs_);
  //   apply_add_(~lhs, rhs.rhs_);
  // }
};

template<typename M1, typename M2>
inline ExprAdd<M1, M2>::ExprAdd(const M1 &lhs,
                                const M2 &rhs) :
                                lhs_(lhs),
                                rhs_(rhs) {
  //
}

// template<typename T, typename M>
// inline const ExprAdd<M, T>
// operator+(T scalar, Matrix<M> &m) {
//   return ExprAdd<M, T>(~m, scalar);
// }
//
// template<typename T, typename M>
// inline const ExprAdd<M, T>
// operator+(Matrix<M> &m, T scalar) {
//   return ExprAdd<M, T>(~m, scalar);
// }

template<typename M1, typename M2>
inline const ExprAdd<M1, M2>
operator+(const Matrix<M1> &m1, const Matrix<M2> &m2) {
  return ExprAdd<M1, M2>(~m1, ~m2);
}

// template<typename T, typename M1, typename M2, typename DT, typename Derived>
// inline void apply_(Matrix<DT> &lhs,
//                    const ExprAdd<M1, M2> &rhs) {
//   apply_(~lhs, *rhs.lhs_);
//   apply_add_(~lhs, *rhs.rhs_);
// }

// template<typename T, typename M1, typename M2>
// inline void apply(Matrix<T, M1> &lhs,
//                   const ExprAdd<M1, M2> &rhs) {
//   (~lhs).apply(*rhs.lhs_);
//   (~lhs).apply_add(*rhs.rhs_);
// }

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_ADD_HPP */
