#ifndef MATH_MATRIX_EXPR_ADD_HPP
#define MATH_MATRIX_EXPR_ADD_HPP

#include "assert.hpp"
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
  const M1 lhs_;
  const M2 rhs_;

public:
  explicit inline ExprAdd(const M1 &lhs, const M2 &rhs);

  inline ExprAdd(const ExprAdd<M1, M2> &m);

// private:
  // A + B
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    std::cout << "result = A + B" << '\n';
    if(!is_expression(rhs.lhs_) && is_equal(~lhs, rhs.lhs_)) {
      apply_add_(~lhs, rhs.rhs_);
    }
    else if(!is_expression(rhs.rhs_) && is_equal(~lhs, rhs.rhs_)) {
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
    std::cout << "result = A + (B + C)" << '\n';
    apply_add_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  // A * (B + C)
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    std::cout << "result = A * (B + C)" << '\n';
    M1 tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_mul_(~lhs, tmp);
  }

  // (A + B)^T = A^T + B^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    std::cout << "result = (A + B)^T" << '\n';
    M1 tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_transpose_(~lhs, tmp);
  }

  // (A + B)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    std::cout << "result = (A + B)^-1" << '\n';
    M1 tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_inverse_(~lhs, tmp);
  }
};

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

template<typename M1, typename M2>
inline const ExprAdd<M1, M2>
operator+(const Matrix<M1> &lhs, const Matrix<M2> &rhs) {
  return ExprAdd<M1, M2>(~lhs, ~rhs);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_ADD_HPP */
