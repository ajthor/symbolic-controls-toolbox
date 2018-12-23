#ifndef MATH_MATRIX_EXPR_TRANSPOSE_HPP
#define MATH_MATRIX_EXPR_TRANSPOSE_HPP

#include "assert.hpp"
#include "matrix.hpp"
#include "expr.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprTranspose
//
template<typename M>
class ExprTranspose : public Expression<Matrix<ExprTranspose<M>>> {
private:
  const M m_;

public:
  explicit inline ExprTranspose(const M &m);

private:
  // A^T
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprTranspose<M> &rhs) {
    std::cout << "result = A^T" << '\n';
    apply_transpose_(~lhs, rhs.m_);
  }

  // A + B^T
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprTranspose<M> &rhs) {
    std::cout << "result = A + B^T" << '\n';
    M tmp(rhs.m_);
    apply_transpose_(tmp, rhs.m_);
    apply_add_(~lhs, tmp);
  }

  // A * B^T
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprTranspose<M> &rhs) {
    std::cout << "result = A * B^T" << '\n';
    M tmp(rhs.m_);
    apply_transpose_(tmp, rhs.m_);
    apply_mul_(~lhs, tmp);
  }

  // (A^T)^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprTranspose<M> &rhs) {
    std::cout << "result = (A^T)^T" << '\n';
    apply_(~lhs, rhs.m_);
  }

  // (A^T)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprTranspose<M> &rhs) {
    std::cout << "result = (A^T)^-1" << '\n';
    apply_inverse_(~lhs, rhs.m_);
  }
};

template<typename M>
inline ExprTranspose<M>::ExprTranspose(const M &m) :
                                       m_(m) {
  //
}

template<typename M>
inline const ExprTranspose<M>
transpose(const Matrix<M> &m) {
  return ExprTranspose<M>(~m);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_TRANSPOSE_HPP */
