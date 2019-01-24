#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/sym/sym.hpp>
#include <symctrl/math/symbolic/sym/sym_t.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_t
//
// template<typename DT>
// inline void sym_t::apply(const Symbolic<DT> &rhs) {
//   // apply_(*ptr_, ~rhs);
// }
//
// template<typename DT>
// inline void sym_t::apply_add(const Symbolic<DT> &rhs) {
//   // apply_add_(*ptr_, ~rhs);
// }
//
// template<typename DT>
// inline void sym_t::apply_sub(const Symbolic<DT> &rhs) {
//   // apply_sub_(*ptr_, ~rhs);
// }
//
// template<typename DT>
// inline void sym_t::apply_mul(const Symbolic<DT> &rhs) {
//   // apply_mul_(*ptr_, ~rhs);
// }
//
// template<typename DT>
// inline void sym_t::apply_div(const Symbolic<DT> &rhs) {
//   // apply_div_(*ptr_, ~rhs);
// }

// ----------------------------------------------------------------------
// sym_t equal
//
// inline bool equal(const sym_t &lhs, const sym_t &rhs) {
//   return equal(lhs.as_ref(), rhs.as_ref());
//   // return lhs.as_ref() == ~rhs;
// }
inline bool equal(const sym_t &lhs, const sym_t &rhs) {
  return lhs.hash() == rhs.hash();
}

template<typename DT>
inline bool equal(const sym_t &lhs, const Symbolic<DT> &rhs) {
  return lhs.hash() == (~rhs).hash();
}

inline bool operator==(const sym_t &lhs, const sym_t &rhs) {
  return equal(lhs, rhs);
}

template<typename DT>
inline bool operator==(const sym_t &lhs, const Symbolic<DT> &rhs) {
  return equal(lhs, ~rhs);
}

inline bool operator!=(const sym_t &lhs, const sym_t &rhs) {
  return !equal(lhs, rhs);
}

template<typename DT>
inline bool operator!=(const sym_t &lhs, const Symbolic<DT> &rhs) {
  return !equal(lhs, ~rhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_HPP
