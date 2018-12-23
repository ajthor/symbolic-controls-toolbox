#ifndef MATH_MATRIX_EXPR_JACOBIAN_HPP
#define MATH_MATRIX_EXPR_JACOBIAN_HPP

#include <symengine/basic.h>
#include <symengine/subs.h>

#include "assert.h"
#include "matrix.hpp"
#include "dense_sym.hpp"
#include "vector_sym.hpp"

template<typename T>
struct derived {};

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// DenseMatrix Jacobian
//
class ExprJacobian : public Expression<Matrix<ExprJacobian>> {
private:
  const SymbolicVector &f_;
  const SymbolicVector &v_;

public:
  explicit inline ExprJacobian(const SymbolicVector &f,
                               const SymbolicVector &v);

private:
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprJacobian &rhs) {
    MATRIX_DEBUG("jacobian apply");
    // derived<DT>::show;
    // std::cout << rhs.f_[0]->__str__() << '\n';
    // SymbolicMatrix tmp;

    // tmp = rhs.f_.jacobian(rhs.v_);
    // apply_(~lhs, tmp.jacobian(rhs.v_));

    (~lhs).apply_jacobian(rhs.f_, rhs.v_);

    // lhs.apply(jacobian(~rhs));
  }

  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprJacobian &rhs) {
    MATRIX_DEBUG("jacobian apply_add");
    apply_add_(~lhs, rhs.f_);
    // lhs.apply_add(jacobian(~rhs));
  }

  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprJacobian &rhs) {
    MATRIX_DEBUG("jacobian apply_mul");
    apply_mul_(~lhs, rhs.f_);
    // lhs.apply_mul(jacobian(~rhs));
  }

  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprJacobian &rhs) {
    MATRIX_DEBUG("jacobian apply_transpose");
    apply_transpose_(~lhs, rhs.f_);
    // lhs.apply_transpose(jacobian(~rhs));
  }

  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprJacobian &rhs) {
    MATRIX_DEBUG("jacobian apply_inverse");
    apply_inverse_(~lhs, rhs.f_);
    // lhs.apply_inverse(jacobian(~rhs));
  }
};

inline ExprJacobian::ExprJacobian(const SymbolicVector &f,
                                  const SymbolicVector &v) :
                                  f_(f),
                                  v_(v) {
  //
}

inline const ExprJacobian
jacobian(const SymbolicVector &f, const SymbolicVector &v) {
  return ExprJacobian(~f, ~v);
}

// ----------------------------------------------------------------------
// SymbolicVector Jacobian
//
template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_jacobian(const Matrix<DT> &f,
                                           const Matrix<DT> &v) {
  // SymbolicMatrix result(v_.size(), f.size());
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
          SymEngine::ssubs((~f)[i], {{(~v)[j], t_}})->diff(t_), {{t_, (~v)[j]}});
      }
    }
  }

//   for (unsigned i = 0; i < result.row_; i++) {
//     for (unsigned j = 0; j < result.col_; j++) {
//         if (is_a<Symbol>(*(x.m_[j]))) {
//             const RCP<const Symbol> x_
//                 = rcp_static_cast<const Symbol>(x.m_[j]);
//             result.m_[i * result.col_ + j] = A.m_[i]->diff(x_);
//         } else {
//             // TODO: Use a dummy symbol
//             const RCP<const Symbol> x_ = symbol("x_");
//             result.m_[i * result.col_ + j] = ssubs(
//                 ssubs(A.m_[i], {{x.m_[j], x_}})->diff(x_), {{x_, x.m_[j]}});
//         }
//     }
// }

  // return result;
  // return *this;
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_JACOBIAN_HPP */
