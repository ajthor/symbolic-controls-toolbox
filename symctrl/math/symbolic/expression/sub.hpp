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
  static constexpr bool isNumeric = (T1::isNumeric && T2::isNumeric);

private:
  const T1 lhs_;
  const T2 rhs_;

public:
  explicit inline ExprSub(const T1 &lhs, const T2 &rhs);

  // inline ExprSub(const ExprSub<Symbolic, T1, T2> &m);

  inline std::string as_str() const;
  inline hash_t hash() const;

  inline bool canEvaluate() const;

private:
  template<typename DT>
  friend inline void
  apply_(Symbolic<DT> &lhs, const ExprSub<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A - B");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_add_(Symbolic<DT> &lhs, const ExprSub<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A + (B - C)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_diff_(Symbolic<DT> &lhs, const ExprSub<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = diff(A - B)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_div_(Symbolic<DT> &lhs, const ExprSub<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A / (B - C)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_mul_(Symbolic<DT> &lhs, const ExprSub<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A * (B - C)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_neg_(Symbolic<DT> &lhs, const ExprSub<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = -(A - B)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_pow_(Symbolic<DT> &lhs, const ExprSub<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = (A - B)^C");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  template<typename DT>
  friend inline void
  apply_sub_(Symbolic<DT> &lhs, const ExprSub<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A - (B - C)");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
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
inline std::string ExprSub<Symbolic, T1, T2>::as_str() const {
  return lhs_.as_str() + " - " + rhs_.as_str();
}

template<typename T1, typename T2>
inline hash_t ExprSub<Symbolic, T1, T2>::hash() const {
  return lhs_.hash() ^ (rhs_.hash() << 1) ^ 150;
}

template<typename T1, typename T2>
inline bool ExprSub<Symbolic, T1, T2>::canEvaluate() const {
  return (lhs_.canEvaluate() && rhs_.canEvaluate());
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
