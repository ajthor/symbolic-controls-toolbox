#ifndef MATH_MATRIX_EXPR_SUB_HPP
#define MATH_MATRIX_EXPR_SUB_HPP

#include "assert.hpp"
#include "matrix.hpp"
#include "expr.hpp"

#include <math/traits/is_expr.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprSub
//
template<typename M1, typename M2>
class ExprSub : public Expression<Matrix<ExprSub<M1, M2>>> {
private:
  const M1 lhs_;
  const M2 rhs_;

public:
  explicit inline ExprSub(const M1 &lhs, const M2 &rhs);

  inline ExprSub(const ExprSub<M1, M2> &m);

private:
  // A - B
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprSub<M1, M2> &rhs) {
    MATRIX_DEBUG("result = A - B");
    if(!is_expr<M1>::value && equal(~lhs, rhs.lhs_)) {
      apply_sub_(~lhs, rhs.rhs_);
    }
    else if(!is_expr<M2>::value && equal(~lhs, rhs.rhs_)) {
      apply_sub_(~lhs, rhs.lhs_);
    }
    else {
      apply_(~lhs, rhs.lhs_);
      apply_sub_(~lhs, rhs.rhs_);
    }
  }

  // A + (B - C)
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprSub<M1, M2> &rhs) {
    MATRIX_DEBUG("result = A + (B - C)");
    apply_add_(~lhs, rhs.lhs_);
    apply_sub_(~lhs, rhs.rhs_);
  }

  // A - (B - C)
  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprSub<M1, M2> &rhs) {
    MATRIX_DEBUG("result = A - (B - C)");
    apply_sub_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  // A * (B - C)
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprSub<M1, M2> &rhs) {
    MATRIX_DEBUG("result = A * (B - C)");
    M1 tmp(rhs.lhs_);
    apply_sub_(tmp, rhs.rhs_);
    apply_mul_(~lhs, tmp);
  }

  // (A - B)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprSub<M1, M2> &rhs) {
    MATRIX_DEBUG("result = (A - B)^-1");
    M1 tmp(rhs.lhs_);
    apply_sub_(tmp, rhs.rhs_);
    apply_inverse_(~lhs, tmp);
  }

  // (A - B)^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprSub<M1, M2> &rhs) {
    MATRIX_DEBUG("result = (A - B)^T");
    M1 tmp(rhs.lhs_);
    apply_sub_(tmp, rhs.rhs_);
    apply_transpose_(~lhs, tmp);
  }
};

// ----------------------------------------------------------------------
// ExprSub Scalar Constructor
//
template<typename M1, typename M2>
inline ExprSub<M1, M2>::ExprSub(const M1 &lhs,
                                const M2 &rhs) :
                                lhs_(lhs),
                                rhs_(rhs) {
  //
}

template<typename M1, typename M2>
inline ExprSub<M1, M2>::ExprSub(const ExprSub<M1, M2> &m) :
                                lhs_(m.lhs_),
                                rhs_(m.rhs_) {
  //
}

// ----------------------------------------------------------------------
// ExprSub Operator
//
template<typename M1, typename M2>
inline const ExprSub<M1, M2>
operator-(const Matrix<M1> &lhs, const Matrix<M2> &rhs) {
  return ExprSub<M1, M2>(~lhs, ~rhs);
}

// ----------------------------------------------------------------------
// ExprSub Scalar Operator
//
template<typename M1, typename M2>
inline auto
operator-(const Matrix<M1> &lhs, const M2 rhs)
-> typename std::enable_if<std::is_scalar<M2>::value, const ExprUnary<M1>>::type {
  M1 tmp(~lhs);
  return ExprUnary<M1>(tmp -= rhs);
}

template<typename M1, typename M2>
inline auto
operator-(const M1 lhs, const Matrix<M2> &rhs)
-> typename std::enable_if<std::is_scalar<M1>::value, const ExprUnary<M2>>::type {
  M2 tmp(~rhs);
  return ExprUnary<M2>(tmp -= lhs);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_SUB_HPP */
