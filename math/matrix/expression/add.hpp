#ifndef MATH_MATRIX_EXPRESSION_ADD_HPP
#define MATH_MATRIX_EXPRESSION_ADD_HPP

#include <math/assert.hpp>
#include <math/matrix/matrix.hpp>
#include <math/matrix/expression/expression.hpp>
#include <math/traits/is_expr.hpp>
#include <math/traits/is_scalar.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprAdd
//
template<typename M1, typename M2>
class ExprAdd : public Expression<Matrix<ExprAdd<M1, M2>>> {
private:
  const M1 lhs_;
  const M2 rhs_;

public:
  explicit inline ExprAdd(const M1 &lhs, const M2 &rhs);

  inline ExprAdd(const ExprAdd<M1, M2> &m);

private:
  // A + B
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    MATH_DEBUG("result = A + B");
    if(!is_expr<M1>::value && equal(~lhs, rhs.lhs_)) {
      apply_add_(~lhs, rhs.rhs_);
    }
    else if(!is_expr<M2>::value && equal(~lhs, rhs.rhs_)) {
      apply_add_(~lhs, rhs.lhs_);
    }
    else {
      apply_(~lhs, rhs.lhs_);
      apply_add_(~lhs, rhs.rhs_);
    }
  }

  // A + (B + C)
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    MATH_DEBUG("result = A + (B + C)");
    apply_add_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  // A - (B + C)
  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    MATH_DEBUG("result = A - (B + C)");
    apply_sub_(~lhs, rhs.lhs_);
    apply_sub_(~lhs, rhs.rhs_);
  }

  // A * (B + C)
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    MATH_DEBUG("result = A * (B + C)");
    M1 tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_mul_(~lhs, tmp);
  }

  // (A + B)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    MATH_DEBUG("result = (A + B)^-1");
    M1 tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_inverse_(~lhs, tmp);
  }

  // (A + B)^T = A^T + B^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    MATH_DEBUG("result = (A + B)^T");
    M1 tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_transpose_(~lhs, tmp);
  }
};

// ----------------------------------------------------------------------
// ExprAdd Scalar Constructor
//
template<typename M1, typename M2>
inline ExprAdd<M1, M2>::ExprAdd(const M1 &lhs,
                                const M2 &rhs) :
                                lhs_(lhs),
                                rhs_(rhs) {
  //
}

template<typename M1, typename M2>
inline ExprAdd<M1, M2>::ExprAdd(const ExprAdd<M1, M2> &m) :
                                lhs_(m.lhs_),
                                rhs_(m.rhs_) {
  //
}

// ----------------------------------------------------------------------
// ExprAdd Operator
//
template<typename M1, typename M2>
inline const ExprAdd<M1, M2>
operator+(const Matrix<M1> &lhs, const Matrix<M2> &rhs) {
  return ExprAdd<M1, M2>(~lhs, ~rhs);
}

// ----------------------------------------------------------------------
// ExprAdd Scalar Operator
//
template<typename M1, typename M2>
inline auto
operator+(const Matrix<M1> &lhs, const M2 rhs)
-> enable_if_scalar_t<M2, const ExprUnary<M1>> {
  M1 tmp(~lhs);
  return ExprUnary<M1>(tmp += rhs);
}

template<typename M1, typename M2>
inline auto
operator+(const M1 lhs, const Matrix<M2> &rhs)
-> enable_if_scalar_t<M1, const ExprUnary<M2>> {
  M2 tmp(~rhs);
  return ExprUnary<M2>(tmp += lhs);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPRESSION_ADD_HPP */
