#ifndef MATH_MATRIX_EXPRESSION_JACOBIAN_HPP
#define MATH_MATRIX_EXPRESSION_JACOBIAN_HPP

#include <symengine/basic.h>
#include <symengine/subs.h>

#include <math/matrix/dense/dense.hpp>
#include <math/traits/is_symbolic.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Jacobian
//
template<typename DT>
auto jacobian(const Matrix<DT> &f, const Matrix<DT> &v)
-> enable_if_symbolic_t<DT, SymbolicDense> {
  SymbolicDense J((~f).size(), (~v).size());

  for(size_t i = 0; i < J.nrows(); i++) {
    for(size_t j = 0; j < J.ncols(); j++) {
      if(SymEngine::is_a<SymEngine::Symbol>(*(~f)[j])) {
        auto t_ = SymEngine::rcp_static_cast<const SymEngine::Symbol>((~v)[j]);
        J[i*J.ncols() + j] = (~f)[i]->diff(t_);
      }
      else {
        auto t_ = SymEngine::symbol("t_");
        J[i*J.ncols() + j] = SymEngine::ssubs(
            SymEngine::ssubs((~f)[i], {{(~v)[j], t_}})->diff(t_),
            {{t_, (~v)[j]}}
          );
      }
    }
  }

  return J;
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPRESSION_JACOBIAN_HPP */
