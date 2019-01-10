#ifndef SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP

#include <string>

#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// BaseSymbolic
//
class BaseSymbolic {
public:
  virtual ~BaseSymbolic() {}
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
};

// ----------------------------------------------------------------------
// Symbolic DT Functions
//
template<typename DT>
inline hash_t hash(Symbolic<DT> &m) {
  return (~m).hash();
}


} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYMBOLIC_HPP
