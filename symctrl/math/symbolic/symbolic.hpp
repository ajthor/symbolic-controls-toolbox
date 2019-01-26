#ifndef SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP

#include <memory>
#include <ostream>

#include <symctrl/assert.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// BaseSymbolic
//
class BaseSymbolic
    : public std::enable_shared_from_this<BaseSymbolic> {
public:
  virtual ~BaseSymbolic() {}

  inline std::shared_ptr<BaseSymbolic> as_ptr();

  virtual std::string as_str() const = 0;
  virtual hash_t hash() const = 0;
};

// ----------------------------------------------------------------------
// BaseSymbolic Member Function Definitions
//
inline std::shared_ptr<BaseSymbolic> BaseSymbolic::as_ptr() {
  return shared_from_this();
}

// ----------------------------------------------------------------------
// Symbolic
//
template<typename DT>
class Symbolic
    : public BaseSymbolic {
public:
  inline DT &operator~();
  inline const DT &operator~() const;

  inline std::shared_ptr<DT> as_ptr();

  std::string as_str() const override;
  inline operator std::string() const;

  hash_t hash() const override;
};

// ----------------------------------------------------------------------
// Symbolic Member Function Definitions
//
template<typename DT>
inline DT &Symbolic<DT>::operator~() {
  return *static_cast<DT *>(this);
}

template<typename DT>
inline const DT &Symbolic<DT>::operator~() const {
  return *static_cast<const DT *>(this);
}

// Uses static_pointer_cast to down cast the shared pointer to the derived type.
template<typename DT>
inline std::shared_ptr<DT> Symbolic<DT>::as_ptr() {
  return std::static_pointer_cast<DT>(shared_from_this());
}

template<typename DT>
std::string Symbolic<DT>::as_str() const {
  return static_cast<const DT &>(*this)._as_str();
}

template<typename DT>
inline Symbolic<DT>::operator std::string() const {
  return static_cast<const DT &>(*this)._as_str();
}

template<typename DT>
hash_t Symbolic<DT>::hash() const {
  return static_cast<const DT &>(*this)._hash();
}

// ----------------------------------------------------------------------
// Ostream Operator
//
template<typename DT>
std::ostream &operator<<(std::ostream &os, const Symbolic<DT> &m) {
  os << m.as_str();
  return os;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP
