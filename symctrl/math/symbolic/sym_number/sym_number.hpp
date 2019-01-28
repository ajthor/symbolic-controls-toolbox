#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_NUMBER_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_NUMBER_HPP

#include <memory>
#include <string>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_number
//
template<typename T>
class sym_number
    : public Symbolic<sym_number<T>> {
public:
  // using type = T;

  using this_type = sym_number<T>;

  // using result_type = sym_number<T>;

private:
  T value_;

  hash_t hash_;

public:
  explicit inline sym_number();
  explicit inline sym_number(const T &m);

  inline sym_number(const sym_number<T> &) = default;
  inline sym_number(sym_number<T> &&) = default;

  // template<typename DT>
  // inline sym_number(const Symbolic<DT> &m);

  inline sym_number<T> &operator=(const T &rhs);

  inline sym_number<T> &operator=(const sym_number<T> &) = default;
  inline sym_number<T> &operator=(sym_number<T> &&) = default;

  // template<typename DT>
  // inline sym_number<T> &operator=(const Symbolic<DT> &rhs);

  inline operator T() const;

  // inline sym_number<T> &operator+=(const T &rhs);
  // inline sym_number<T> &operator-=(const T &rhs);
  // inline sym_number<T> &operator*=(const T &rhs);
  // inline sym_number<T> &operator/=(const T &rhs);

  // template<typename DT>
  // inline void apply(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline void apply_add(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline void apply_sub(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline void apply_mul(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline void apply_div(const Symbolic<DT> &rhs);

  inline std::string _as_str() const;
  inline hash_t _hash() const;

  inline T value() const;
};

// ----------------------------------------------------------------------
// sym_number Constructor
//
template<typename T>
inline sym_number<T>::sym_number()
    : value_(T()),
      hash_(hash_string{}(std::to_string(T()))) {}

template<typename T>
inline sym_number<T>::sym_number(const T &m)
    : value_(m),
      hash_(hash_string{}(std::to_string(m))) {}

// template<typename T>
// template<typename DT>
// inline sym_number<T>::sym_number(const Symbolic<DT> &m) {
//   apply_(*this, ~m);
// }

// ----------------------------------------------------------------------
// sym_number Assignment Operator
//
template<typename T>
inline sym_number<T> &sym_number<T>::operator=(const T &rhs) {
  value_ = rhs;
  hash_ = hash_string{}(std::to_string(rhs));

  return *this;
}

// template<typename T>
// template<typename DT>
// inline sym_number<T> &sym_number<T>::operator=(const Symbolic<DT> &rhs) {
//   apply_(*this, ~rhs);
//
//   return *this;
// }

// ----------------------------------------------------------------------
// sym_number Member Function Definitions
//
template<typename T>
inline sym_number<T>::operator T() const {
  return value_;
}

template<typename T>
inline std::string sym_number<T>::_as_str() const {
  return std::to_string(value_);
}

// template<typename T>
// inline T &sym_number<T>::value() {
//   return value_;
// }
//
// template<typename T>
// inline const T &sym_number<T>::value() const {
//   return value_;
// }

template<typename T>
inline hash_t sym_number<T>::_hash() const {
  return hash_;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_NUMBER_SYM_NUMBER_HPP
