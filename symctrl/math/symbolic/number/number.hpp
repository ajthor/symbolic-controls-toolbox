#ifndef SYMCTRL_MATH_SYMBOLIC_NUMBER_NUMBER_HPP
#define SYMCTRL_MATH_SYMBOLIC_NUMBER_NUMBER_HPP

#include <functional>
#include <string>

#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/expression/symbolic.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/type_traits/is_string.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Symbolic Number
//
template<typename T>
class Number : public Symbolic<Number<T>> {
public:
  using type = T;

  using this_type = Number<T>;

  using result_type = Number<T>;

private:
  T value_;

  hash_t hash_;

public:
  explicit inline Number();

  inline Number(const T &v);
  inline Number(const Number<T> &m);

  template<typename DT>
  inline Number(const Symbolic<DT> &m);

  inline Number<T> &operator=(const T &rhs);
  inline Number<T> &operator=(const Number<T> &rhs);

  template<typename DT>
  inline Number<T> &operator=(const Symbolic<DT> &rhs);

  inline operator T() const;

  inline Number<T> &operator+=(const T &rhs);
  inline Number<T> &operator-=(const T &rhs);
  inline Number<T> &operator*=(const T &rhs);
  inline Number<T> &operator/=(const T &rhs);

  template<typename DT>
  inline void apply(const Number<DT> &rhs);
  template<typename DT>
  inline void apply_add(const Number<DT> &rhs);
  template<typename DT>
  inline void apply_sub(const Number<DT> &rhs);
  template<typename DT>
  inline void apply_mul(const Number<DT> &rhs);
  template<typename DT>
  inline void apply_div(const Number<DT> &rhs);

  inline auto value() const -> const result_type&;

  // inline T &value();
  // inline const T &value() const;

  inline hash_t hash() const;
};

// ----------------------------------------------------------------------
// Number Constructor
//
template<typename T>
inline Number<T>::Number() {
  value_ = T(0);
  hash_ = hash_f<T>{}(T());
}

template<typename T>
inline Number<T>::Number(const T &value) {
  value_ = value;
  hash_ = hash_f<T>{}(value);
}

template<typename T>
inline Number<T>::Number(const Number<T> &m) :
                         value_(m.value_),
                         hash_(m.hash_) {
  //
}

template<typename T>
template<typename DT>
inline Number<T>::Number(const Symbolic<DT> &m) {
  apply_(*this, ~m);
}

// ----------------------------------------------------------------------
// Number Assignment Operator
//
template<typename T>
inline Number<T> &Number<T>::operator=(const T &rhs) {
  value_ = rhs;
  hash_ = hash_f<T>{}(rhs);

  return *this;
}

template<typename T>
inline Number<T> &Number<T>::operator=(const Number<T> &rhs) {
  value_ = rhs.value();
  hash_ = rhs.hash();

  return *this;
}

template<typename T>
template<typename DT>
inline Number<T> &Number<T>::operator=(const Symbolic<DT> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

// ----------------------------------------------------------------------
// Number Member Function Definitions
//
template<typename T>
inline Number<T>::operator T() const {
  return value_;
}

template<typename T>
inline auto Number<T>::value() const -> const result_type& {
  return *this;
}

// template<typename T>
// inline T &Number<T>::value() {
//   return value_;
// }
//
// template<typename T>
// inline const T &Number<T>::value() const {
//   return value_;
// }

template<typename T>
inline hash_t Number<T>::hash() const {
  return hash_;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_NUMBER_NUMBER_HPP
