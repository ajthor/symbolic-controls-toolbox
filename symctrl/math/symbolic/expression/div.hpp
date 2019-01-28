#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_DIV_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_DIV_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/div.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/type_traits/is_numeric.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprDiv
//
template<typename T1, typename T2>
class ExprDiv<Symbolic, T1, T2> :
  public Expression<Symbolic<ExprDiv<Symbolic, T1, T2>>> {
public:
  // using type = typename T1::type;

  // using result_type = result_type_t<T1>;

private:
  const T1 lhs_;
  const T2 rhs_;

public:
  explicit inline ExprDiv(const T1 &lhs, const T2 &rhs);
  // inline ExprDiv(const ExprDiv<Symbolic, T1, T2> &m);

  inline std::string _as_str() const;
  inline hash_t _hash() const;

private:
  // // A + B
  // template<typename DT>
  // friend inline void
  // apply_(Symbolic<DT> &lhs, const ExprDiv<Symbolic, T1, T2> &rhs) {
  //   SYMCTRL_DEBUG("result = A * B");
  //   // Handle multiplication by zero or one.
  //   if(is_numeric_s<T1>::value) {
  //     if(lhs_ == 0) {
  //       apply_(~lhs, Number<int>(0));
  //     }
  //     else if(lhs_ == 1) {
  //       apply_(~lhs, rhs.rhs_);
  //     }
  //     else {
  //       apply_(~lhs, rhs.lhs_);
  //       apply_mul_(~lhs, rhs.rhs_);
  //     }
  //   }
  //   else if(is_numeric_s<T2>::value) {
  //     if(rhs_ == 0) {
  //       apply_(~lhs, Number<int>(0));
  //     }
  //     else if(rhs_ == 1) {
  //       apply_(~lhs, rhs.lhs_);
  //     }
  //     else {
  //       apply_(~lhs, rhs.lhs_);
  //       apply_mul_(~lhs, rhs.rhs_);
  //     }
  //   }
  //   else {
  //     apply_(~lhs, rhs.lhs_);
  //     apply_mul_(~lhs, rhs.rhs_);
  //   }
  // }
  //
  // // A * (B * C)
  // template<typename DT>
  // friend inline void
  // apply_mul_(Symbolic<DT> &lhs, const ExprDiv<Symbolic, T1, T2> &rhs) {
  //   SYMCTRL_DEBUG("result = A * (B * C)");
  //   result_type tmp(rhs.lhs_);
  //   apply_mul_(tmp, rhs.rhs_);
  //   apply_mul_(~lhs, tmp);
  // }
};

// ----------------------------------------------------------------------
// ExprDiv Constructor
//
template<typename T1, typename T2>
inline ExprDiv<Symbolic, T1, T2>::ExprDiv(const T1 &lhs, const T2 &rhs)
    : lhs_(lhs),
      rhs_(rhs) {}

// template<typename T1, typename T2>
// inline ExprDiv<Symbolic, T1, T2>::ExprDiv(ExprDiv<Symbolic, T1, T2> &m)
//     : lhs_(m.lhs_),
//       rhs_(m.rhs_) {}

// ----------------------------------------------------------------------
// ExprDiv Type Conversion Operator
//
// template<typename T1, typename T2>
// ExprDiv<Symbolic, T1, T2>::operator ExprDiv<Symbolic, T1, T2>::type() const {
//   result_type r;
//   apply_(r, *this);
//
//   return r;
// }

// ----------------------------------------------------------------------
// ExprDiv Member Function Definitions
//
template<typename T1, typename T2>
inline std::string ExprDiv<Symbolic, T1, T2>::_as_str() const {
  return (~lhs_).as_str() + "/" + (~rhs_).as_str();
}

template<typename T1, typename T2>
inline hash_t ExprDiv<Symbolic, T1, T2>::_hash() const {
  return lhs_.hash() ^ (rhs_.hash() << 1) ^ 250;
}

// ----------------------------------------------------------------------
// ExprDiv Operator
//
template<typename T1, typename T2>
inline auto operator/(const Symbolic<T1> &lhs, const Symbolic<T2> &rhs)
-> const ExprDiv<Symbolic, T1, T2> {
  return ExprDiv<Symbolic, T1, T2>(~lhs, ~rhs);
}

// // ----------------------------------------------------------------------
// // ExprDiv Scalar Operator
// //
// template<typename T1, typename T2>
// inline auto
// operator*(const Symbolic<T1> &lhs, const T2 rhs)
// -> enable_if_scalar_t<T2, const ExprUnary<Symbolic, T1>> {
//   T1 tmp(~lhs);
//   return ExprUnary<Symbolic, T1>(tmp *= rhs);
// }
//
// template<typename T1, typename T2>
// inline auto
// operator*(const T1 lhs, const Symbolic<T2> &rhs)
// -> enable_if_scalar_t<T1, const ExprUnary<Symbolic, T2>> {
//   T2 tmp(~rhs);
//   return ExprUnary<Symbolic, T2>(tmp *= lhs);
// }

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_DIV_HPP
