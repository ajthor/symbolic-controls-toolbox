#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SUB_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SUB_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/sub.hpp>
#include <symctrl/math/symbolic/expression/unary.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/type_traits/is_scalar.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprSub
//
template<typename T1, typename T2>
class ExprSub<Symbolic, T1, T2> :
  public Expression<Symbolic<ExprSub<Symbolic, T1, T2>>> {
public:
  // using type = typename T1::type;

  // using result_type = result_type_t<T1>;

private:
  const T1 lhs_;
  const T2 rhs_;

public:
  explicit inline ExprSub(const T1 &lhs, const T2 &rhs);

  // inline ExprSub(const ExprSub<Symbolic, T1, T2> &m);

  inline std::string _as_str() const;
  inline hash_t _hash() const;

private:
  // A + B
  template<typename DT>
  friend inline void
  apply_(Symbolic<DT> &lhs, const ExprSub<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A - B");
    apply_(~lhs, rhs.lhs_);
    apply_sub_(~lhs, rhs.rhs_);
  }
};

// ----------------------------------------------------------------------
// ExprSub Constructor
//
template<typename T1, typename T2>
inline ExprSub<Symbolic, T1, T2>::ExprSub(const T1 &lhs, const T2 &rhs)
    : lhs_(lhs),
      rhs_(rhs) {}

// template<typename T1, typename T2>
// inline ExprSub<Symbolic, T1, T2>::ExprSub(const ExprSub<Symbolic, T1, T2> &m) :
//                                           lhs_(m.lhs_),
//                                           rhs_(m.rhs_) {
//   //
// }

// ----------------------------------------------------------------------
// ExprSub Type Conversion Operator
//
// template<typename T1, typename T2>
// ExprSub<Symbolic, T1, T2>::operator ExprSub<Symbolic, T1, T2>::type() const {
//   result_type r;
//   apply_(r, *this);
//
//   return r;
// }

// ----------------------------------------------------------------------
// ExprSub Member Function Definitions
//
template<typename T1, typename T2>
inline std::string ExprSub<Symbolic, T1, T2>::_as_str() const {
  return lhs_.as_str() + " - " + rhs_.as_str();
}

template<typename T1, typename T2>
inline hash_t ExprSub<Symbolic, T1, T2>::_hash() const {
  return lhs_.hash() ^ (rhs_.hash() << 1) ^ 150;
}

// ----------------------------------------------------------------------
// ExprSub Operator
//
template<typename T1, typename T2>
inline auto operator-(const Symbolic<T1> &lhs, const Symbolic<T2> &rhs)
-> const ExprSub<Symbolic, T1, T2> {
  return ExprSub<Symbolic, T1, T2>(~lhs, ~rhs);
}

// // ----------------------------------------------------------------------
// // ExprSub Scalar Operator
// //
// template<typename T1, typename T2>
// inline auto
// operator-(const Symbolic<T1> &lhs, const T2 rhs)
// -> enable_if_scalar_t<T2, const ExprUnary<Symbolic, T1>> {
//   T1 tmp(~lhs);
//   return ExprUnary<Symbolic, T1>(tmp -= rhs);
// }
//
// template<typename T1, typename T2>
// inline auto
// operator-(const T1 lhs, const Symbolic<T2> &rhs)
// -> enable_if_scalar_t<T1, const ExprUnary<Symbolic, T2>> {
//   T2 tmp(~rhs);
//   tmp *= -1;
//   return ExprUnary<Symbolic, T2>(tmp += lhs);
// }

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SUB_HPP
