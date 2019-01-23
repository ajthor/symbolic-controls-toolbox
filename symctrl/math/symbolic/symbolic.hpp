#ifndef SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP

#include <memory>
#include <ostream>
#include <type_traits>

#include <symctrl/assert.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

class BaseSymbolicVisitor;

// ----------------------------------------------------------------------
// BaseSymbolic
//
class BaseSymbolic {
public:
  // using this_type = BaseSymbolic;

  virtual ~BaseSymbolic() {}

  virtual BaseSymbolic &get_ref() = 0;
  virtual const BaseSymbolic &get_ref() const = 0;

  // virtual operator std::string() const = 0;

  // virtual bool apply_(const Symbolic<DT> &rhs);
  // virtual bool apply_add_(const Symbolic<DT> &rhs);
  // virtual bool apply_sub_(const Symbolic<DT> &rhs);
  // virtual bool apply_mul_(const Symbolic<DT> &rhs);
  // virtual bool apply_div_(const Symbolic<DT> &rhs);
  // virtual bool equal_(const Symbolic<DT> &rhs);

  virtual void accept(BaseSymbolicVisitor &visitor) = 0;
  virtual void accept(BaseSymbolicVisitor &visitor) const = 0;
};

// ----------------------------------------------------------------------
// Symbolic
//
template< typename DT>                    // Derived type.
          // typename Base = BaseSymbolic >  // Base type.
class Symbolic
    : public BaseSymbolic {
public:
  using derived_type = DT;

  inline DT &operator~() {
    return *static_cast<DT *>(this);
  }

  inline const DT &operator~() const {
    return *static_cast<const DT *>(this);
  }

  operator std::string() const;

  Symbolic<DT> &get_ref() override {
    SYMCTRL_DEBUG("Getting ref.");
    // return *static_cast<DT *>(this);
    return *this;
  }
  const Symbolic<DT> &get_ref() const override {
    SYMCTRL_DEBUG("Getting const ref.");
    // return *static_cast<const DT *>(this);
    return *this;
  }

  void accept(BaseSymbolicVisitor &visitor) override;
  void accept(BaseSymbolicVisitor &visitor) const override;

  // inline void accept(BaseSymbolicVisitor &visitor);

  // Shared Pointer
  // std::shared_ptr<const Symbolic<DT>> get_ptr() const {
  //   return static_cast<const DT &>(*this).shared_from_this();
  // }
};

// ----------------------------------------------------------------------
// Symbolic Member Function Definitions
//
template<typename DT>
Symbolic<DT>::operator std::string() const {
  return static_cast<const DT &>(*this).as_str();
}

// ----------------------------------------------------------------------
// Ostream Operator
//
template<typename DT>
std::ostream &operator<<(std::ostream &os, const Symbolic<DT> &m) {
    os << (~m).as_str();
    return os;
}

// ----------------------------------------------------------------------
// Symbolic Derived Type Function Definitions
//
template<typename DT>
inline hash_t hash(const Symbolic<DT> &m) {
  return (~m).hash();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP
