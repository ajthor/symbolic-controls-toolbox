#ifndef MATH_MATRIX_SYMBOLIC_HPP
#define MATH_MATRIX_SYMBOLIC_HPP

#include <symengine/add.h>
#include <symengine/mul.h>
#include <symengine/basic.h>
#include <symengine/constants.h>

namespace Controls {
namespace Math {

using RCPBasic = SymEngine::RCP<const SymEngine::Basic>;

// ----------------------------------------------------------------------
// equal
//
template<>
inline bool equal(const RCPBasic lhs, const RCPBasic rhs) {
  return SymEngine::eq(*lhs, *rhs);
}

template<>
inline bool is_default(const RCPBasic v) {
  return SymEngine::eq(*v, *SymEngine::zero);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_SYMBOLIC_HPP */
