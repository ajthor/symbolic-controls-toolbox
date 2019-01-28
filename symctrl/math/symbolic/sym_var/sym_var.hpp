#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_VAR_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_VAR_HPP

#include <memory>
#include <string>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_var
//
class sym_var
    : public Symbolic<sym_var> {
public:
  using this_type = sym_var;

private:
  std::string name_;

  hash_t hash_;

public:
  explicit inline sym_var();
  explicit inline sym_var(std::string name);

  inline sym_var(const sym_var &) = default;
  inline sym_var(sym_var &&) = default;

  inline sym_var &operator=(std::string name);

  inline sym_var &operator=(const sym_var &) = default;
  inline sym_var &operator=(sym_var &&) = default;

  inline std::shared_ptr<sym_var> as_ptr();

  inline std::string _as_str() const;
  inline hash_t _hash() const;
};

// ----------------------------------------------------------------------
// sym_var Constructor
//
inline sym_var::sym_var()
    : name_(std::string()),
      hash_(0) {}

inline sym_var::sym_var(std::string name)
    : name_(name),
      hash_(hash_string{}(name)) {}

// ----------------------------------------------------------------------
// sym_var Assignment Operator
//

inline sym_var &sym_var::operator=(std::string name) {
  name_ = name;
  hash_ = hash_string{}(name);
  return *this;
}

// ----------------------------------------------------------------------
// Symbolic Member Function Definitions
//
inline std::string sym_var::_as_str() const {
  return name_;
}

inline hash_t sym_var::_hash() const {
  return hash_;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_VAR_HPP
