#ifndef MATH_MATRIX_EXPRESSION_NEG_HPP
#define MATH_MATRIX_EXPRESSION_NEG_HPP

#include <math/assert.hpp>
#include <math/matrix/matrix.hpp>
#include <math/matrix/expression/expression.hpp>

#include <math/traits/is_expr.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprNeg
//
template<typename M>
class ExprNeg : public Expression<Matrix<ExprNeg<M>>> {
private:
  const M m_;

public:
  explicit inline ExprNeg(const M &m);

  inline ExprNeg(const ExprNeg<M> &m);

  inline const M get_operand();

private:
  // -A
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    MATH_DEBUG("result = -A");
    apply_(~lhs, rhs.m_);
    ~lhs *= -1;
  }

  // A + -B
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    MATH_DEBUG("result = A + -B");
    apply_sub_(~lhs, rhs.m_);
  }

  // A - -B
  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    MATH_DEBUG("result = A - -B");
    apply_add_(~lhs, rhs.m_);
  }

  // A * -B
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    MATH_DEBUG("result = A * -B");
    apply_mul_(~lhs, rhs.m_);
    ~lhs *= -1;
  }

  // (-A)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    MATH_DEBUG("result = (-A)^-1");
    apply_inverse_(~lhs, rhs.m_);
    ~lhs *= -1;
  }

  // (-A)^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    MATH_DEBUG("result = (-A)^T");
    apply_transpose_(~lhs, rhs.m_);
    ~lhs *= -1;
  }
};

template<typename M>
inline ExprNeg<M>::ExprNeg(const M &m) :
                           m_(m) {
  //
}

template<typename M>
inline ExprNeg<M>::ExprNeg(const ExprNeg<M> &m) :
                           m_(m.m_) {
  //
}

template<typename M>
inline const M ExprNeg<M>::get_operand() {
  return m_;
}

// ----------------------------------------------------------------------
// ExprNeg Operator
//
template<typename M>
inline const ExprNeg<M>
operator-(const Matrix<M> &m) {
  return ExprNeg<M>(~m);
}

template<typename M>
inline const M
operator-(const ExprNeg<M> &m) {
  return m.get_operand();
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPRESSION_NEG_HPP */
