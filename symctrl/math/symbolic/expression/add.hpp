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
class ExprAdd<Symbolic, T1, T2> :
  public Expression<Symbolic<ExprAdd<Symbolic, T1, T2>>> {
public:
  using type = typename T1::type;

  using result_type = result_type_t<T1>;

private:
  const T1 lhs_;
  const T2 rhs_;

public:
  explicit inline ExprAdd(const T1 &lhs, const T2 &rhs);

  inline ExprAdd(const ExprAdd<Symbolic, T1, T2> &m);

  operator type() const;

  inline hash_t hash() const;

private:
  // A + B
  template<typename DT>
  friend inline void
  apply_(Symbolic<DT> &lhs, const ExprAdd<Symbolic, T1, T2> &rhs) {
    SYMCTRL_DEBUG("result = A + B");
    apply_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }
};

// ----------------------------------------------------------------------
// ExprAdd Constructor
//
template<typename T1, typename T2>
inline ExprAdd<Symbolic, T1, T2>::ExprAdd(const T1 &lhs,
                                          const T2 &rhs) :
                                          lhs_(lhs),
                                          rhs_(rhs) {
  //
}

template<typename T1, typename T2>
inline ExprAdd<Symbolic, T1, T2>::ExprAdd(const ExprAdd<Symbolic, T1, T2> &m) :
                                          lhs_(m.lhs_),
                                          rhs_(m.rhs_) {
  //
}

// ----------------------------------------------------------------------
// ExprAdd Type Conversion Operator
//
template<typename T1, typename T2>
ExprAdd<Symbolic, T1, T2>::operator ExprAdd<Symbolic, T1, T2>::type() const {
  result_type r;
  apply_(r, *this);

  return r;
}

// ----------------------------------------------------------------------
// ExprAdd Member Function Definitions
//
template<typename T1, typename T2>
inline hash_t ExprAdd<Symbolic, T1, T2>::hash() const {
  result_type r;
  apply_(r, *this);

  return r.hash();
}

// ----------------------------------------------------------------------
// ExprAdd Operator
//
template<typename T1, typename T2>
inline const ExprAdd<Symbolic, T1, T2>
operator+(const Symbolic<T1> &lhs, const Symbolic<T2> &rhs) {
  return ExprAdd<Symbolic, T1, T2>(~lhs, ~rhs);
}

// ----------------------------------------------------------------------
// ExprAdd Scalar Operator
//
template<typename T1, typename T2>
inline auto
operator+(const Symbolic<T1> &lhs, const T2 rhs)
-> enable_if_scalar_t<T2, const ExprUnary<Symbolic, T1>> {
  T1 tmp(~lhs);
  return ExprUnary<Symbolic, T1>(tmp += rhs);
}

template<typename T1, typename T2>
inline auto
operator+(const T1 lhs, const Symbolic<T2> &rhs)
-> enable_if_scalar_t<T1, const ExprUnary<Symbolic, T2>> {
  T2 tmp(~rhs);
  return ExprUnary<Symbolic, T2>(tmp += lhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_ADD_HPP
