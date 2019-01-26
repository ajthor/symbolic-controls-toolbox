#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_POW_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_POW_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/pow.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprPow
//
template<typename T1, typename T2>
class ExprPow<Symbolic, T1, T2>
    : public Expression<Symbolic<ExprPow<Symbolic, T1, T2>>> {
public:

private:
  const T1 &lhs_;
  const T2 &rhs_;

public:
  explicit inline ExprPow(const T1 &lhs, const T2 &rhs);
  // inline ExprPow(ExprPow<Symbolic, sym_t, sym_t> &m);

  inline std::string _as_str() const;
  inline hash_t _hash() const;
};

// ----------------------------------------------------------------------
// ExprPow Constructor
//
template<typename T1, typename T2>
inline ExprPow<Symbolic, T1, T2>::ExprPow(const T1 &lhs, const T2 &rhs)
    : lhs_(lhs),
      rhs_(rhs) {}

// template<>
// inline ExprPow<Symbolic, sym_t, sym_t>::ExprPow(ExprPow<Symbolic, sym_t, sym_t> &m)
//     : lhs_(m.lhs_),
//       rhs_(m.rhs_) {}

// ----------------------------------------------------------------------
// ExprPow Member Function Definitions
//
template<typename T1, typename T2>
inline std::string ExprPow<Symbolic, T1, T2>::_as_str() const {
  return lhs_.as_str() + "^" + rhs_.as_str();
}

template<typename T1, typename T2>
inline hash_t ExprPow<Symbolic, T1, T2>::_hash() const {
  return lhs_.hash() ^ (rhs_.hash() << 1) ^ 275;
}

// ----------------------------------------------------------------------
// ExprPow Operator
//
template<typename T1, typename T2>
inline auto operator^(const Symbolic<T1> &lhs, const Symbolic<T2> &rhs)
-> const ExprPow<Symbolic, T1, T2> {
  return ExprPow<Symbolic, T1, T2>(~lhs, ~rhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_POW_HPP
