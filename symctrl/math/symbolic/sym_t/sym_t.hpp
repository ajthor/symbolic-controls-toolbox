#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_T_SYM_T_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_T_SYM_T_HPP

#include <memory>
#include <string>

#include <type_traits>

#include <symctrl/assert.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/sym_var/sym_var.hpp>
#include <symctrl/math/symbolic/sym_number/sym_number.hpp>
#include <symctrl/type_traits/is_numeric.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_t
//
class sym_t
    : public Symbolic<sym_t> {
public:

private:
  std::shared_ptr<BaseSymbolic> ptr_;

public:
  explicit inline sym_t(std::string name);

  inline sym_t(const int &m);
  inline sym_t(const double &m);

  // template<typename DT>
  // inline sym_t(const Symbolic<DT> &m);
  template<typename DT>
  inline sym_t(const Symbolic<DT> &&m);

  // inline sym_t(const sym_t &m) noexcept;
  // inline sym_t(sym_t &&m) noexcept;

  // inline sym_t &operator=(std::string name);

  // template<typename DT>
  // inline sym_t &operator=(const Symbolic<DT> &rhs);
  template<typename DT>
  inline sym_t &operator=(const Symbolic<DT> &&rhs);

  // inline sym_t &operator=(const sym_t &rhs) noexcept;
  // inline sym_t &operator=(sym_t &&rhs) noexcept;

  // template<typename DT>
  // inline sym_t &operator+=(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline sym_t &operator-=(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline sym_t &operator*=(const Symbolic<DT> &rhs);
  // template<typename DT>
  // inline sym_t &operator/=(const Symbolic<DT> &rhs);
  template<typename T>
  inline sym_t &operator+=(const T &rhs);
  template<typename T>
  inline sym_t &operator-=(const T &rhs);
  template<typename T>
  inline sym_t &operator*=(const T &rhs);
  template<typename T>
  inline sym_t &operator/=(const T &rhs);

  inline std::string _as_str() const;
  inline hash_t _hash() const;
};

// ----------------------------------------------------------------------
// sym_t Constructor
//
inline sym_t::sym_t(std::string name)
    : ptr_(std::make_shared<sym_var>(name)) {}

inline sym_t::sym_t(const int &m)
    : ptr_(std::make_shared<sym_number<int>>(m)) {}

inline sym_t::sym_t(const double &m)
    : ptr_(std::make_shared<sym_number<double>>(m)) {}

// template<typename DT>
// inline sym_t::sym_t(const Symbolic<DT> &m)
//     : ptr_(std::move((~m).as_ptr())) {}

template<typename DT>
inline sym_t::sym_t(const Symbolic<DT> &&m)
    // : ptr_((~m).as_ptr()) {}
    : ptr_(std::make_shared<DT>(std::move(~m))) {}

// inline sym_t::sym_t(const sym_t &m) noexcept
//     : ptr_(m.ptr_->as_ptr()) {}
//
// inline sym_t::sym_t(sym_t &&m) noexcept
//     : ptr_(std::move(m.ptr_->as_ptr())) {}

// ----------------------------------------------------------------------
// sym_t Assignment Operator
//
// template<typename DT>
// inline sym_t &sym_t::operator=(const Symbolic<DT> &m) {
//   ptr_.reset(std::move((~m).as_ptr()));
//   return *this;
// }

template<typename DT>
inline sym_t &sym_t::operator=(const Symbolic<DT> &&m) {
  SYMCTRL_DEBUG("sym_t move assignment operator");
  // ptr_.reset(std::move((~m)));
  ptr_ = std::make_shared<DT>(std::move(~m));
  // ptr_ = (~m).as_ptr();
  return *this;
}

// inline sym_t &operator=(const sym_t &rhs) {
//
// }

// inline sym_t &sym_t::operator=(sym_t &&rhs) noexcept {
//   ptr_.reset(std::move(rhs.as_ptr()));
//   return *this;
// }

// ----------------------------------------------------------------------
// sym_t Member Function Definitions
//
inline std::string sym_t::_as_str() const {
  return ptr_->as_str();
}

inline hash_t sym_t::_hash() const {
  return ptr_->hash();
}

// ----------------------------------------------------------------------
// sym_t Ostream Operator
//
std::ostream &operator<<(std::ostream &os, const sym_t &m) {
  os << m.as_str();
  return os;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_T_SYM_T_HPP
