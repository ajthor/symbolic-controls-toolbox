#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_ADD_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_ADD_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/add.hpp>
#include <symctrl/math/symbolic/expression/unary.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/type_traits/is_scalar.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprAdd
//
template<typename T1, typename T2>
class ExprAdd<Symbolic, T1, T2>
    : public Expression<Symbolic<ExprAdd<Symbolic, T1, T2>>> {
public:

private:
  const T1 &lhs_;
  const T2 &rhs_;

public:
  explicit inline ExprAdd(const T1 &lhs, const T2 &rhs);
  // inline ExprAdd(ExprAdd<Symbolic, sym_t, sym_t> &m);

  inline std::string _as_str() const;
  inline hash_t _hash() const;
};

// ----------------------------------------------------------------------
// ExprAdd Constructor
//
template<typename T1, typename T2>
inline ExprAdd<Symbolic, T1, T2>::ExprAdd(const T1 &lhs, const T2 &rhs)
    : lhs_(lhs),
      rhs_(rhs) {}

// template<>
// inline ExprAdd<Symbolic, sym_t, sym_t>::ExprAdd(ExprAdd<Symbolic, sym_t, sym_t> &m)
//     : lhs_(m.lhs_),
//       rhs_(m.rhs_) {}

// ----------------------------------------------------------------------
// ExprAdd Member Function Definitions
//
template<typename T1, typename T2>
inline std::string ExprAdd<Symbolic, T1, T2>::_as_str() const {
  return (~lhs_).as_str() + " + " + (~rhs_).as_str();
}

template<typename T1, typename T2>
inline hash_t ExprAdd<Symbolic, T1, T2>::_hash() const {
  return 0;
}

// ----------------------------------------------------------------------
// ExprAdd Operator
//
template<typename T1, typename T2>
inline auto operator+(const Symbolic<T1> &lhs, const Symbolic<T2> &rhs)
-> const ExprAdd<Symbolic, T1, T2> {
  return ExprAdd<Symbolic, T1, T2>(~lhs, ~rhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_ADD_HPP
