#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_VARIABLE_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_VARIABLE_HPP

#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/expression/symbolic.hpp>
#include <symctrl/math/symbolic/variable/variable.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Variable Expressions
//
template<typename DT>
inline void Variable::apply(const Symbolic<DT> &rhs) {
  // value_
}

template<typename DT>
inline void Variable::apply_add(const Symbolic<DT> &rhs) {

}

template<typename DT>
inline void Variable::apply_sub(const Symbolic<DT> &rhs) {

}

template<typename DT>
inline void Variable::apply_mul(const Symbolic<DT> &rhs) {

}

template<typename DT>
inline void Variable::apply_div(const Symbolic<DT> &rhs) {

}

// ----------------------------------------------------------------------
// Variable Equal
//
inline bool equal(const Variable &lhs, const Variable &rhs) {
  return lhs.hash() == rhs.hash();
}

template<typename DT>
inline bool equal(const Symbolic<DT> &lhs, const Variable &rhs) {
  return (~lhs).hash() == rhs.hash();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_VARIABLE_HPP
