#ifndef MATH_MATRIX_EXPRESSION_JACOBIAN_HPP
#define MATH_MATRIX_EXPRESSION_JACOBIAN_HPP

#include <symengine/basic.h>
#include <symengine/subs.h>

#include <math/assert.hpp>
#include <math/matrix/matrix.hpp>
#include <math/matrix/expression/expression.hpp>
#include <math/matrix/expression/unary.hpp>
#include <math/matrix/expression/dense.hpp>

#include <math/traits/is_symbolic.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SymbolicDense Jacobian
//
template<typename DT>
inline auto
jacobian(const Matrix<DT> &f, const Matrix<DT> &v)
-> enable_if_symbolic_t<DT, const ExprUnary<SymbolicDense>> {
  SymbolicDense tmp;
  tmp.jacobian(~f, ~v);
  return ExprUnary<SymbolicDense>(tmp);
}

// ----------------------------------------------------------------------
// SymbolicDense Jacobian Member Function
//
template<>
template<typename DT>
inline auto
SymbolicDense::jacobian(const Matrix<DT> &f, const Matrix<DT> &v)
-> enable_if_symbolic_t<DT> {
  n_ = (~f).size();
  m_ = (~v).size();

  v_.resize(n_*m_);

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

#endif /* end of include guard: MATH_MATRIX_EXPRESSION_JACOBIAN_HPP */
