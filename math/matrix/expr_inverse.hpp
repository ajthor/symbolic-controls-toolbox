#ifndef MATH_MATRIX_EXPR_INVERSE_HPP
#define MATH_MATRIX_EXPR_INVERSE_HPP

#include "assert.hpp"
#include "matrix.hpp"
#include "expr.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprInverse
//
template<typename M>
class ExprInverse : public Expression<Matrix<ExprInverse<M>>> {
private:
  const M &m_;

public:
  explicit inline ExprInverse(const M &m);

  // A^-1
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprInverse<M> &rhs) {
    MATRIX_DEBUG("A^-1");
    apply_inverse_(~lhs, rhs.m_);
  }

  // A + B^-1
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprInverse<M> &rhs) {
    MATRIX_DEBUG("A + B^-1");
    M tmp(rhs.m_);
    apply_inverse_(tmp, rhs.m_);
    apply_add_(~lhs, tmp);
  }

  // A * B^-1
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprInverse<M> &rhs) {
    MATRIX_DEBUG("A * B^-1");
    M tmp(rhs.m_);
    apply_inverse_(tmp, rhs.m_);
    apply_mul_(~lhs, tmp);
  }

  // (A^-1)^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprInverse<M> &rhs) {
    MATRIX_DEBUG("(A^-1)^T");
    apply_inverse_(~lhs, rhs.m_);
  }

  // (A^-1)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprInverse<M> &rhs) {
    MATRIX_DEBUG("(A^-1)^-1");
    apply_inverse_(~lhs, rhs.m_);
  }
};

template<typename M>
inline ExprInverse<M>::ExprInverse(const M &m) :
                                   m_(m) {
  //
}

template<typename M>
inline const ExprInverse<M>
inverse(const Matrix<M> &m) {
  return ExprInverse<M>(~m);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_INVERSE_HPP */