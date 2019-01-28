#ifndef SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_RV_HPP
#define SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_RV_HPP

#include <memory>
#include <string>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/shims/make_unique.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_rv
//
class sym_rv
    : public Symbolic<sym_rv> {
public:
  using this_type = sym_rv;

private:
  std::string name_;
  std::unique_ptr<RandomNumberDistribution> dist_;

  hash_t hash_;

public:
  explicit inline sym_rv();
  explicit inline sym_rv(std::string name, RandomNumberDistribution &dist);
  inline sym_rv(const sym_rv &m);

  inline sym_rv &operator=(std::string name);
  inline sym_rv &operator=(const sym_rv &rhs);

  inline std::shared_ptr<sym_rv> as_ptr();

  inline std::string _as_str() const;
  inline hash_t _hash() const;
};

// ----------------------------------------------------------------------
// sym_rv Constructor
//
inline sym_rv::sym_rv()
    : name_(std::string()),
      hash_(0) {}

inline sym_rv::sym_rv(const sym_rv &m)
    : name_(m.name_),
      hash_(m.hash_) {}

inline sym_rv::sym_rv(std::string name, RandomNumberDistribution &dist)
    : name_(name),
      hash_(hash_string{}(name)),
      dist_(make_unique(dist)) {}

// ----------------------------------------------------------------------
// sym_rv Assignment Operator
//
inline sym_rv &sym_rv::operator=(const sym_rv &rhs) {
  name_ = rhs.as_str();
  hash_ = rhs.hash();
  return *this;
}

inline sym_rv &sym_rv::operator=(std::string name) {
  name_ = name;
  hash_ = hash_string{}(name);
  return *this;
}

// ----------------------------------------------------------------------
// Symbolic Member Function Definitions
//
inline std::string sym_rv::_as_str() const {
  return name_;
}

inline hash_t sym_rv::_hash() const {
  return hash_;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_SYM_VAR_SYM_RV_HPP
