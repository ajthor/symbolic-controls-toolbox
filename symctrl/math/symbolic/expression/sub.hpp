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
class ExprSub<sym_t, T1, T2> :
  public Expression<sym_t<ExprSub<sym_t, T1, T2>>> {
public:
  using type = typename T1::type;

  using result_type = result_type_t<T1>;

private:
  const T1 lhs_;
  const T2 rhs_;

public:
  explicit inline ExprSub(const T1 &lhs, const T2 &rhs);

  inline ExprSub(const ExprSub<sym_t, T1, T2> &m);

  // operator type() const;

  // inline ExprSub<sym_t, T1, T2> &value();
  // inline const ExprSub<sym_t, T1, T2> &as_ref() const;

  inline std::string as_str() const;

  inline hash_t hash() const;

private:
  // A + B
  template<typename DT>
  friend inline void
  apply_(sym_t<DT> &lhs, const ExprSub<sym_t, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A - B");
    apply_(~lhs, rhs.lhs_);
    apply_sub_(~lhs, rhs.rhs_);
  }
};

// ----------------------------------------------------------------------
// ExprSub Constructor
//
template<typename T1, typename T2>
inline ExprSub<sym_t, T1, T2>::ExprSub(const T1 &lhs,
                                          const T2 &rhs) :
                                          lhs_(lhs),
                                          rhs_(rhs) {
  //
}

template<typename T1, typename T2>
inline ExprSub<sym_t, T1, T2>::ExprSub(const ExprSub<sym_t, T1, T2> &m) :
                                          lhs_(m.lhs_),
                                          rhs_(m.rhs_) {
  //
}

// ----------------------------------------------------------------------
// ExprSub Type Conversion Operator
//
// template<typename T1, typename T2>
// ExprSub<sym_t, T1, T2>::operator ExprSub<sym_t, T1, T2>::type() const {
//   result_type r;
//   apply_(r, *this);
//
//   return r;
// }

// ----------------------------------------------------------------------
// ExprSub Member Function Definitions
//
// template<typename T1, typename T2>
// inline auto ExprSub<sym_t, T1, T2>::as_ref() const
// -> const ExprSub<sym_t, T1, T2>& {
//   return *this;
// }

template<typename T1, typename T2>
inline std::string ExprSub<sym_t, T1, T2>::as_str() const {
  return lhs_.as_str() + " - " + rhs_.as_str();
}

template<typename T1, typename T2>
inline hash_t ExprSub<sym_t, T1, T2>::hash() const {
  result_type r;
  apply_(r, *this);

  return r.hash();
}

// ----------------------------------------------------------------------
// ExprSub Operator
//
template<typename T1, typename T2>
inline const ExprSub<sym_t, T1, T2>
operator-(const sym_t<T1> &lhs, const sym_t<T2> &rhs) {
  return ExprSub<sym_t, T1, T2>(~lhs, ~rhs);
}

// ----------------------------------------------------------------------
// ExprSub Scalar Operator
//
template<typename T1, typename T2>
inline auto
operator-(const sym_t<T1> &lhs, const T2 rhs)
-> enable_if_scalar_t<T2, const ExprUnary<sym_t, T1>> {
  T1 tmp(~lhs);
  return ExprUnary<sym_t, T1>(tmp -= rhs);
}

template<typename T1, typename T2>
inline auto
operator-(const T1 lhs, const sym_t<T2> &rhs)
-> enable_if_scalar_t<T1, const ExprUnary<sym_t, T2>> {
  T2 tmp(~rhs);
  tmp *= -1;
  return ExprUnary<sym_t, T2>(tmp += lhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SUB_HPP
