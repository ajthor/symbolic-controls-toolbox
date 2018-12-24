#ifndef MATH_MATRIX_EXPR_JACOBIAN_HPP
#define MATH_MATRIX_EXPR_JACOBIAN_HPP

#include <symengine/basic.h>
#include <symengine/subs.h>

#include "assert.h"
#include "matrix.hpp"
#include "expr.hpp"
#include "symbolic_dense.hpp"

#include <math/traits/is_symbolic.hpp>

template<typename T>
struct derived {};

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// DenseMatrix Jacobian
//
template<typename M1, typename M2>
class ExprJacobian : public Expression<Matrix<ExprJacobian<M1, M2>>> {
private:
  const M1 f_;
  const M2 v_;

public:
  explicit inline ExprJacobian(const M1 &f,
                               const M2 &v);

private:
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprJacobian &rhs) {
    MATRIX_DEBUG("jacobian(A)");
    DT tmp(~lhs);
    tmp.apply_jacobian(rhs.f_, rhs.v_);
    apply_(~lhs, tmp);
  }

  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprJacobian &rhs) {
    MATRIX_DEBUG("A + jacobian(B)");
    DT tmp(~lhs);
    tmp.apply_jacobian(rhs.f_, rhs.v_);
    apply_add_(~lhs, tmp);
  }

  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprJacobian &rhs) {
    MATRIX_DEBUG("A * jacobian(B)");
    DT tmp(~lhs);
    tmp.apply_jacobian(rhs.f_, rhs.v_);
    apply_mul_(~lhs, tmp);
  }

  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprJacobian &rhs) {
    MATRIX_DEBUG("(jacobian(A))^T");
    DT tmp(~lhs);
    tmp.apply_jacobian(rhs.f_, rhs.v_);
    apply_transpose_(~lhs, tmp);
  }

  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprJacobian &rhs) {
    MATRIX_DEBUG("(jacobian(A))^-1");
    DT tmp(~lhs);
    tmp.apply_jacobian(rhs.f_, rhs.v_);
    apply_inverse_(~lhs, tmp);
  }
};

template<typename M1, typename M2>
inline ExprJacobian<M1, M2>::ExprJacobian(const M1 &f,
                                          const M2 &v) :
                                          f_(f),
                                          v_(v) {
  //
}

template<typename M1, typename M2>
inline const ExprJacobian<M1, M2>
jacobian(const Matrix<M1> &f, const Matrix<M2> &v) {
  return ExprJacobian<M1, M2>(~f, ~v);
}

// ----------------------------------------------------------------------
// SymbolicMatrix Jacobian
//
template<>
template<typename DT>
inline auto
SymbolicMatrix::apply_jacobian(const Matrix<DT> &f, const Matrix<DT> &v)
-> enable_if_symbolic_t<DT> {
  n_ = (~f).size();
  m_ = (~f).size();

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      if(SymEngine::is_a<SymEngine::Symbol>(*(~f)[j])) {
        auto t_ = SymEngine::rcp_static_cast<const SymEngine::Symbol>((~v)[j]);
        v_[i*m_ + j] = (~f)[i]->diff(t_);
      }
      else {
        auto t_ = SymEngine::symbol("t_");
        v_[i*m_ + j] = SymEngine::ssubs(
            SymEngine::ssubs((~f)[i], {{(~v)[j], t_}})->diff(t_),
            {{t_, (~v)[j]}}
          );
      }
    }
  }
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_JACOBIAN_HPP */
