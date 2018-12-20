#ifndef MATH_MATRIX_EXPR_ADD_HPP
#define MATH_MATRIX_EXPR_ADD_HPP

#include "matrix.hpp"
#include "expr.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprAdd
//
template<typename T, typename M1, typename M2>
class ExprAdd : public Matrix<T, ExprAdd<T, M1, M2>> {
private:
  const M1 &lhs_;
  const M2 &rhs_;

public:
  explicit inline ExprAdd(const M1 &lhs, const M2 &rhs);

  template<typename DT, typename Derived>
  friend inline void apply_(Matrix<DT, Derived> &lhs,
                            const ExprAdd<T, M1, M2> &rhs) {
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT, typename Derived>
  friend inline void apply_add_(Matrix<DT, Derived> &lhs,
                                const ExprAdd<T, M1, M2> &rhs) {
    apply_add_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }
};

template<typename T, typename M1, typename M2>
inline ExprAdd<T, M1, M2>::ExprAdd(const M1 &lhs,
                                   const M2 &rhs) :
                                   lhs_(lhs),
                                   rhs_(rhs) {
  //
}

template<typename T, typename M>
inline const ExprAdd<T, M, T>
operator+(T scalar, Matrix<T, M> &m) {
  return ExprAdd<T, M, T>(~m, scalar);
}

template<typename T, typename M>
inline const ExprAdd<T, M, T>
operator+(Matrix<T, M> &m, T scalar) {
  return ExprAdd<T, M, T>(~m, scalar);
}

template<typename T, typename M1, typename M2>
inline const ExprAdd<T, M1, M2>
operator+(Matrix<T, M1> &m1, Matrix<T, M2> &m2) {
  return ExprAdd<T, M1, M2>(~m1, ~m2);
}

// template<typename T, typename M1, typename M2, typename DT, typename Derived>
// inline void apply_(Matrix<DT, Derived> &lhs,
//                    const ExprAdd<T, M1, M2> &rhs) {
//   apply_(~lhs, *rhs.lhs_);
//   apply_add_(~lhs, *rhs.rhs_);
// }

// template<typename T, typename M1, typename M2>
// inline void apply(Matrix<T, M1> &lhs,
//                   const ExprAdd<T, M1, M2> &rhs) {
//   (~lhs).apply(*rhs.lhs_);
//   (~lhs).apply_add(*rhs.rhs_);
// }

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_ADD_HPP */
