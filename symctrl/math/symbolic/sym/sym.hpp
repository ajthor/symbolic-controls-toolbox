#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_SYM_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_SYM_HPP

#include <memory>
#include <string>

#include <symctrl/assert.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym
//
class sym
    : public Symbolic<sym> {
public:
  using this_type = sym;

private:
  std::string name_;

  hash_t hash_;

public:
  explicit inline sym();
  explicit inline sym(std::string name);
  inline sym(const sym &m);

  inline sym &operator=(std::string name);
  inline sym &operator=(const sym &rhs);

  inline std::shared_ptr<sym> as_ptr();

  inline std::string _as_str() const;
  inline hash_t _hash() const;
};

// ----------------------------------------------------------------------
// sym Constructor
//
inline sym::sym()
    : name_(std::string()),
      hash_(0) {}

inline sym::sym(const sym &m)
    : name_(m.name_),
      hash_(m.hash_) {}

inline sym::sym(std::string name)
    : name_(name),
      hash_(hash_string{}(name)) {}

// ----------------------------------------------------------------------
// sym Assignment Operator
//
inline sym &sym::operator=(const sym &rhs) {
  name_ = rhs.as_str();
  hash_ = rhs.hash();
  return *this;
}

inline sym &sym::operator=(std::string name) {
  name_ = name;
  hash_ = hash_string{}(name);
  return *this;
}

// ----------------------------------------------------------------------
// Symbolic Member Function Definitions
//
inline std::string sym::_as_str() const {
  return name_;
}

inline hash_t sym::_hash() const {
  return hash_;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_SYM_HPP
