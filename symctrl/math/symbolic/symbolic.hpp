#ifndef SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP

#include <memory>

#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// BaseSymbolic
//
class BaseSymbolic {
public:
  // virtual ~BaseSymbolic() {}

  // virtual void evaluate() = 0;
};

// ----------------------------------------------------------------------
// Symbolic
//
template<typename DT>
class Symbolic : public BaseSymbolic {
public:
  inline DT &operator~() {
    return *static_cast<DT *>(this);
  }
  inline const DT &operator~() const {
    return *static_cast<const DT *>(this);
  }

  // void evaluate() {
  //   value((this)->operator~());
  // }
};

// ----------------------------------------------------------------------
// Symbolic DT Functions
//
// template<typename DT>
// inline typename DT::result_type value(const Symbolic<DT> &m) {
//   return (~m).value();
// }

// template<typename DT>
// inline const DT::result_type value(const Symbolic<DT> &m) {
//   return (~m).value();
// }

template<typename DT>
inline hash_t hash(const Symbolic<DT> &m) {
  return (~m).hash();
}

// ----------------------------------------------------------------------
// sym_t
//
class sym_t {
private:
  // std::shared_ptr<BaseSymbolic> ptr_;
  BaseSymbolic *ptr_;

public:
  explicit inline sym_t();
  explicit inline sym_t(const sym_t &m);
  explicit inline sym_t(sym_t &&m);

  template<typename DT>
  inline sym_t(const Symbolic<DT> &m);
  template<typename DT>
  inline sym_t(Symbolic<DT> &&m);

  inline sym_t &operator=(const sym_t &rhs);
  inline sym_t &operator=(sym_t &&rhs);

  template<typename DT>
  inline sym_t &operator=(const Symbolic<DT> &rhs);
  template<typename DT>
  inline sym_t &operator=(Symbolic<DT> &&rhs);
};

// ----------------------------------------------------------------------
// sym_t Constructor
//
inline sym_t::sym_t()
  : ptr_(nullptr) {
  //
}

inline sym_t::sym_t(const sym_t &m) {
  ptr_ = m.ptr_;
}

inline sym_t::sym_t(sym_t &&m)
  : ptr_(std::move(m.ptr_)) {
}

template<typename DT>
inline sym_t::sym_t(const Symbolic<DT> &m) {
  // ptr_ = std::unique_ptr<Symbolic<DT>>(&m);
  // ptr_ = &m;
}

template<typename DT>
inline sym_t::sym_t(Symbolic<DT> &&m)
  : ptr_(std::move(m)) {
  // ptr_ = std::unique_ptr<Symbolic<DT>>(&m);
  // ptr_ = &m;
}

// ----------------------------------------------------------------------
// sym_t Assignment Operator
//
inline sym_t &sym_t::operator=(const sym_t &rhs) {
  // ptr_ = std::unique_ptr<BaseSymbolic>(std::move(rhs.ptr_));
  ptr_ = rhs.ptr_;

  return *this;
}

inline sym_t &sym_t::operator=(sym_t &&rhs) {
  // ptr_ = std::unique_ptr<BaseSymbolic>(std::move(rhs.ptr_));
  ptr_ = rhs.ptr_;

  return *this;
}

template<typename DT>
inline sym_t &sym_t::operator=(const Symbolic<DT> &rhs) {
  // ptr_ = std::unique_ptr<Symbolic<DT>>(rhs);
  ptr_ = &rhs;

  return *this;
}

template<typename DT>
inline sym_t &sym_t::operator=(Symbolic<DT> &&rhs) {
  // ptr_ = std::unique_ptr<Symbolic<DT>>(rhs);
  ptr_ = &rhs;

  return *this;
}

template<typename DT>
inline bool operator==(const sym_t &lhs, const Symbolic<DT> &rhs) {

  return false;
  // return ~lhs == ~rhs;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP
