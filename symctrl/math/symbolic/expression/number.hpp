#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_NUMBER_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_NUMBER_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/expression/symbolic.hpp>
#include <symctrl/math/symbolic/number/number.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Number Expressions
//
template<typename T>
inline Number<T> &Number<T>::operator+=(const T &rhs) {
  value_ += rhs;
  hash_ = hash_f<T>{}(value_);
  return *this;
}

template<typename T>
inline Number<T> &Number<T>::operator-=(const T &rhs) {
  value_ -= rhs;
  hash_ = hash_f<T>{}(value_);
  return *this;
}

template<typename T>
inline Number<T> &Number<T>::operator*=(const T &rhs) {
  value_ *= rhs;
  hash_ = hash_f<T>{}(value_);
  return *this;
}

template<typename T>
inline Number<T> &Number<T>::operator/=(const T &rhs) {
  value_ /= rhs;
  hash_ = hash_f<T>{}(value_);
  return *this;
}

template<typename T>
template<typename DT>
inline void Number<T>::apply(const Symbolic<DT> &rhs) {
  value_ = (~rhs);
  hash_ = (~rhs).hash();
}

template<typename T>
template<typename DT>
inline void Number<T>::apply_add(const Symbolic<DT> &rhs) {
  value_ += (~rhs);
  hash_ = hash_f<T>{}(value_);
}

template<typename T>
template<typename DT>
inline void Number<T>::apply_sub(const Symbolic<DT> &rhs) {
  value_ -= (~rhs);
  hash_ = hash_f<T>{}(value_);
}

template<typename T>
template<typename DT>
inline void Number<T>::apply_mul(const Symbolic<DT> &rhs) {
  value_ *= (~rhs);
  hash_ = hash_f<T>{}(value_);
}

template<typename T>
template<typename DT>
inline void Number<T>::apply_div(const Symbolic<DT> &rhs) {
  value_ /= (~rhs);
  hash_ = hash_f<T>{}(value_);
}

// ----------------------------------------------------------------------
// Number Equal
//
// template<typename T>
// inline bool equal(const Number<T> &lhs, const Number<T> &rhs) {
//   std::cout << "Number == Number" << '\n';
//   return lhs.hash() == rhs.hash();
// }

template<typename T, typename DT>
inline bool equal(const Number<T> &lhs, const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("Number == Symbolic");
  return lhs.hash() == (~rhs).hash();
}


} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_NUMBER_HPP
