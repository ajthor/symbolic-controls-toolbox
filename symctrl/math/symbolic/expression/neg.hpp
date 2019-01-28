#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_NEG_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_NEG_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/expression.hpp>
#include <symctrl/math/expression/neg.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprNeg
//
template<typename T>
class ExprNeg<Symbolic, T>
    : public Expression<Symbolic<ExprNeg<Symbolic, T>>> {
public:
  // using type = typename T::type;

  // using result_type = result_type_t<T>;

private:
  const T m_;

public:
  explicit inline ExprNeg(const T &m);

  // inline ExprNeg(ExprNeg<Symbolic, T> &m);

  inline std::string _as_str() const;
  inline hash_t _hash() const;

private:
  template<typename DT>
  friend inline void
  apply_(Symbolic<DT> &lhs, const ExprNeg<Symbolic, T> &rhs) {
    apply_(~lhs, rhs.m_);
  }
};

// ----------------------------------------------------------------------
// ExprNeg Constructor
//
template<typename T>
inline ExprNeg<Symbolic, T>::ExprNeg(const T &m)
    : m_(m) {}

// template<typename T>
// inline ExprNeg<Symbolic, T>::ExprNeg(ExprNeg<Symbolic, T> &m)
//     : m_(m.m_) {}

// ----------------------------------------------------------------------
// ExprNeg Type Conversion Operator
//
// template<typename T>
// ExprNeg<Symbolic, T>::operator ExprNeg<Symbolic, T>::type() const {
//   result_type r;
//   apply_(r, *this);
//
//   return r;
// }

// ----------------------------------------------------------------------
// ExprNeg Member Function Definitions
//
template<typename T>
inline std::string ExprNeg<Symbolic, T>::_as_str() const {
  return "-" + m_.as_str();
}

template<typename T>
inline hash_t ExprNeg<Symbolic, T>::_hash() const {
  return m_.hash() ^ 50;
}

// ----------------------------------------------------------------------
// ExprNeg Negation Operator
//
template<typename T>
inline auto operator-(const Symbolic<T> &m)
-> const ExprNeg<Symbolic, T> {
  return ExprNeg<Symbolic, T>(~m);
}

template<typename T>
inline const T operator-(const ExprNeg<Symbolic, T> &m) {
  return m.get_operand();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_NEG_HPP
