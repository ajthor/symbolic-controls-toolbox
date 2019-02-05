#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_NUMBER_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_NUMBER_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/expression/symbolic.hpp>
#include <symctrl/math/symbolic/sym_number/sym_number.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/type_traits/is_numeric.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_number Expressions
//
// template<typename T>
// inline sym_number<T> &sym_number<T>::operator+=(const T &rhs) {
//   real_ += rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }
//
// template<typename T>
// inline sym_number<T> &sym_number<T>::operator-=(const T &rhs) {
//   real_ -= rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }
//
// template<typename T>
// inline sym_number<T> &sym_number<T>::operator*=(const T &rhs) {
//   real_ *= rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }
//
// template<typename T>
// inline sym_number<T> &sym_number<T>::operator/=(const T &rhs) {
//   real_ /= rhs;
//   hash_ = hash_f<T>{}(real_);
//   return *this;
// }

template<typename T>
template<typename DT>
inline void sym_number<T>::apply(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number<T>::apply");
  real_ = (~rhs).real_value();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_add(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number<T>::apply_add");
  real_ += (~rhs).real_value();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_diff(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number<T>::apply_diff");
  real_ = T(0);
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_div(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number<T>::apply_div");
  real_ /= (~rhs).real_value();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_mul(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number<T>::apply_mul");
  real_ *= (~rhs).real_value();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_neg(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number<T>::apply_neg");
  real_ = -1*(~rhs).real_value();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_pow(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number<T>::apply_pow");
  // real_ = (~rhs).real_value();
  if(hash_) {
    hash_ = 0;
  }
}

template<typename T>
template<typename DT>
inline void sym_number<T>::apply_sub(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number<T>::apply_sub");
  real_ -= (~rhs).real_value();
  if(hash_) {
    hash_ = 0;
  }
}

// ----------------------------------------------------------------------
// sym_number Equal
//
template<typename T>
inline bool equal(const sym_number<T> &lhs, const sym_number<T> &rhs) {
  std::cout << "sym_number == sym_number" << '\n';
  return lhs.real_value() == rhs.real_value();
}

template<typename T, typename DT>
inline bool equal(const sym_number<T> &lhs, const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_number == Symbolic");
  return lhs.hash() == (~rhs).hash();
}

template<typename T>
inline auto operator==(const sym_number<T> &lhs, const T &rhs)
-> enable_if_numeric_t<T, bool> {
  SYMCTRL_DEBUG("sym_number == Number");
  // return lhs.hash() == hash_string{}(std::to_string(rhs));
  return lhs.real_value() == rhs;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_NUMBER_HPP
