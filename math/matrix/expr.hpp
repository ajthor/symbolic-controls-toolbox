#ifndef MATH_MATRIX_EXPR_HPP
#define MATH_MATRIX_EXPR_HPP

#include <type_traits>

#include "matrix.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Expression
//
template<typename DT>
class Expression : public DT {};

// ----------------------------------------------------------------------
// ExprUnary
//
template<typename M>
class ExprUnary : public Expression<Matrix<ExprUnary<M>>> {
private:
  const M m_;

public:
  explicit inline ExprUnary(const M &m);

  inline ExprUnary(const ExprUnary<M> &m);

  inline const M get_operand();

private:
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_add_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_sub_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_mul_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_inverse_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_transpose_(~lhs, rhs.m_);
  }
};

template<typename M>
inline ExprUnary<M>::ExprUnary(const M &m) :
                               m_(m) {
  //
}

template<typename M>
inline ExprUnary<M>::ExprUnary(const ExprUnary<M> &m) :
                               m_(m.m_) {
  //
}

template<typename M>
inline const M ExprUnary<M>::get_operand() {
  return m_;
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_HPP */
