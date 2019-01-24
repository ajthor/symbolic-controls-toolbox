#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_SYM_T_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_SYM_T_HPP

#include <memory>
#include <string>

#include <symctrl/assert.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/sym/sym.hpp>

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

  template<typename DT>
  inline sym_t(Symbolic<DT> &m);
  template<typename DT>
  inline sym_t(const Symbolic<DT> &&m);

  inline sym_t(sym_t &m);
  inline sym_t(sym_t &&m);

  // inline sym_t &operator=(std::string name);

  template<typename DT>
  inline sym_t &operator=(Symbolic<DT> &rhs);

  inline std::string _as_str() const;
  inline hash_t _hash() const;
};

// ----------------------------------------------------------------------
// sym_t Constructor
//
inline sym_t::sym_t(std::string name)
    : ptr_(std::make_shared<sym>(name)) {}

template<typename DT>
inline sym_t::sym_t(Symbolic<DT> &m)
    : ptr_((~m).as_ptr()) {}

template<typename DT>
inline sym_t::sym_t(const Symbolic<DT> &&m)
    : ptr_(std::make_shared<DT>(std::move(~m))) {}

inline sym_t::sym_t(sym_t &m)
    : ptr_(m.ptr_->as_ptr()) {}

inline sym_t::sym_t(sym_t &&m)
    : ptr_(std::move(m.ptr_->as_ptr())) {}

// ----------------------------------------------------------------------
// sym_t Assignment Operator
//
template<typename DT>
inline sym_t &sym_t::operator=(Symbolic<DT> &m) {
  ptr_ = (~m).as_ptr();
  return *this;
}

// inline sym_t &sym_t::operator=(sym &&m) {
//   ptr_ = m.as_ptr();
//   return *this;
// }

// ----------------------------------------------------------------------
// sym_t Member Function Definitions
//
inline std::string sym_t::_as_str() const {
  return ptr_->as_str();
}

// inline sym_t::operator std::string() const {
//   return ptr_->as_str();
// }

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

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_SYM_T_HPP
