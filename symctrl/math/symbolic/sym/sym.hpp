#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_SYM_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_SYM_HPP

#include <memory>
#include <type_traits>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_t
//
class sym_t
    : public Symbolic<sym_t> {
    // : public BaseSymbolic {
public:
  using type = sym_t;

  using this_type = sym_t;

  using result_type = sym_t;

// private:
  BaseSymbolic *ptr_;

public:
  // explicit inline sym_t();
  inline sym_t(const sym_t &m);
  template<typename DT>
  inline sym_t(Symbolic<DT> &m);
  template<typename DT>
  inline sym_t(Symbolic<DT> &&m);

  inline sym_t &operator=(const sym_t &rhs);
  template<typename DT>
  inline sym_t &operator=(Symbolic<DT> &rhs);
  template<typename DT>
  inline sym_t &operator=(Symbolic<DT> &&rhs);

  inline BaseSymbolic &operator*();
  inline const BaseSymbolic &operator*() const;
  inline const BaseSymbolic *operator->() const;

  // template<typename DT>
  // inline const DT *cast() const;

  template<typename DT>
  inline void apply(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_add(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_sub(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_mul(const Symbolic<DT> &rhs);
  template<typename DT>
  inline void apply_div(const Symbolic<DT> &rhs);

  inline std::string as_str() const;

  inline hash_t hash() const;

  template<typename DT>
  inline bool eq_(const Symbolic<DT> &rhs) const {
    return equal(*ptr_, ~rhs);
  }
};

// ----------------------------------------------------------------------
// sym_t Constructor
//
// inline sym_t::sym_t()
//     : ptr_() {
//   SYMCTRL_DEBUG("sym_t default constructor");
// }

inline sym_t::sym_t(const sym_t &m)
    : ptr_(m.ptr_) {
  SYMCTRL_DEBUG("sym_t copy constructor");
}

template<typename DT>
inline sym_t::sym_t(Symbolic<DT> &m)
    : ptr_(&m) {
  SYMCTRL_DEBUG("sym_t copy constructor");
}

template<typename DT>
inline sym_t::sym_t(Symbolic<DT> &&m)
    : ptr_(&m) {
  SYMCTRL_DEBUG("sym_t move constructor");
}

// ----------------------------------------------------------------------
// sym_t Assignment Operator
//
template<typename DT>
inline sym_t &sym_t::operator=(Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_t copy assignment operator");
  ptr_ = ~rhs;

  return *this;
}
template<typename DT>
inline sym_t &sym_t::operator=(Symbolic<DT> &&rhs) {
  SYMCTRL_DEBUG("sym_t move assignment operator");
  ptr_ = &rhs;

  return *this;
}

// ----------------------------------------------------------------------
// sym_t Pointer Dereference Operators
//
inline BaseSymbolic &sym_t::operator*() {
  SYMCTRL_DEBUG("Pointer dereference operator (const).");
  return *ptr_;
}

inline const BaseSymbolic &sym_t::operator*() const {
  SYMCTRL_DEBUG("Pointer dereference operator.");
  return *ptr_;
}

inline const BaseSymbolic *sym_t::operator->() const {
  SYMCTRL_DEBUG("Arrow operator.");
  return ptr_;
}

// template<typename DT>
// inline const DT *sym_t::cast() const {
//   return dynamic_cast<const DT *>(ptr_);
// }

// ----------------------------------------------------------------------
// sym_t Member Function Definitions
//
// template<typename DT>
// inline sym_t::operator Symbolic<DT>() const {
//   return ptr_->as_ref();
// }

// inline auto sym_t::as_ref() const
// -> const Symbolic<sym_t>& {
//   return *this;
// }

inline std::string sym_t::as_str() const {
  // return ptr_->operator std::string();
  // return ptr_.as_str();
  // return ptr_->get_ref().operator std::string();
  return std::string();
}

inline hash_t sym_t::hash() const {
  // return ptr_->as_ref().hash();
  // std::cout << "sym_t hash" << '\n';
  // return ptr_->as_ref().hash();
  return 0;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_SYM_HPP
