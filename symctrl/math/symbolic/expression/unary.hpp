#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_UNARY_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_UNARY_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/unary.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprUnary
//
template<typename T>
class ExprUnary<Symbolic, T>
    : public Expression<Symbolic<ExprUnary<Symbolic, T>>> {
public:
  using type = typename T::type;

  using result_type = result_type_t<T>;

private:
  sym_t m_;

public:
  explicit inline ExprUnary(const T &m);

  inline ExprUnary(ExprUnary<Symbolic, T> &m);

  // operator type() const;

  // inline ExprUnary<Symbolic, T> &value();
  // inline const ExprUnary<Symbolic, T> &as_ref() const;

  inline std::string _as_str() const;

  inline hash_t _hash() const;

private:
  template<typename DT>
  friend inline void
  apply_(Symbolic<DT> &lhs, const ExprUnary<Symbolic, T> &rhs) {
    apply_(~lhs, rhs.m_);
  }
};

// ----------------------------------------------------------------------
// ExprUnary Constructor
//
template<typename T>
inline ExprUnary<Symbolic, T>::ExprUnary(const T &m)
    : m_(m) {}

template<typename T>
inline ExprUnary<Symbolic, T>::ExprUnary(ExprUnary<Symbolic, T> &m)
    : m_(m.m_) {}

// ----------------------------------------------------------------------
// ExprUnary Type Conversion Operator
//
// template<typename T>
// ExprUnary<Symbolic, T>::operator ExprUnary<Symbolic, T>::type() const {
//   result_type r;
//   apply_(r, *this);
//
//   return r;
// }

// ----------------------------------------------------------------------
// ExprUnary Member Function Definitions
//
// template<typename T>
// inline auto ExprUnary<Symbolic, T>::as_ref() const
// -> const ExprUnary<Symbolic, T>& {
//   return *this;
// }

template<typename T>
inline std::string ExprUnary<Symbolic, T>::_as_str() const {
  return m_.as_str();
}

template<typename T>
inline hash_t ExprUnary<Symbolic, T>::_hash() const {
  // result_type r;
  // apply_(r, *this);
  //
  // return r.hash();
  return 0;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_UNARY_HPP
