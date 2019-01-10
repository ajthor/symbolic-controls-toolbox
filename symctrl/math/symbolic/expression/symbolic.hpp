#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYMBOLIC_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYMBOLIC_HPP

#include <symctrl/math/symbolic/symbolic.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Assignment Functions
//
template<typename D1, typename D2>
inline void apply_(Symbolic<D1> &lhs, const Symbolic<D2> &rhs) {
  (~lhs).apply(~rhs);
}

template<typename D1, typename D2>
inline void apply_add_(Symbolic<D1> &lhs, const Symbolic<D2> &rhs) {
  (~lhs).apply_add(~rhs);
}

template<typename D1, typename D2>
inline void apply_sub_(Symbolic<D1> &lhs, const Symbolic<D2> &rhs) {
  (~lhs).apply_sub(~rhs);
}

template<typename D1, typename D2>
inline void apply_mul_(Symbolic<D1> &lhs, const Symbolic<D2> &rhs) {
  (~lhs).apply_mul(~rhs);
}

template<typename D1, typename D2>
inline void apply_div_(Symbolic<D1> &lhs, const Symbolic<D2> &rhs) {
  (~lhs).apply_div(~rhs);
}

// ----------------------------------------------------------------------
// Symbolic Equality Operator
//
template<typename D1, typename D2>
inline bool operator==(const Symbolic<D1> &lhs, const Symbolic<D2> &rhs) {
  return equal(~lhs, ~rhs);
}

template<typename D1, typename D2>
inline bool operator!=(const Symbolic<D1> &lhs, const Symbolic<D2> &rhs) {
  return !equal(~lhs, ~rhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYMBOLIC_HPP
