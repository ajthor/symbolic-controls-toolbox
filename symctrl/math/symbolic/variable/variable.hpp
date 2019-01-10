#ifndef SYMCTRL_MATH_SYMBOLIC_VARIABLE_VARIABLE_HPP
#define SYMCTRL_MATH_SYMBOLIC_VARIABLE_VARIABLE_HPP

#include <string>

#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/expression/symbolic.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/type_traits/is_string.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Symbolic Variable
//
class Variable : public Symbolic<Variable> {
public:
  using result_type = Variable;

private:
  hash_t hash_;

public:
  explicit inline Variable(const std::string &str);

  inline Variable(const Variable &m);

  template<typename DT>
  inline Variable(const Symbolic<DT> &m);

  template<typename T>
  inline auto operator=(const T &rhs)
  -> enable_if_string_t<T, Variable&>;

  inline Variable &operator=(const Variable &rhs);

  template<typename DT>
  inline Variable &operator=(const Symbolic<DT> &rhs);

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

  inline hash_t hash() const;
};

// ----------------------------------------------------------------------
// Variable Constructor
//
inline Variable::Variable(const std::string &str) {
  hash_ = hash_string{}(str);
}

inline Variable::Variable(const Variable &m) :
                          hash_(m.hash_) {
  //
}

template<typename DT>
inline Variable::Variable(const Symbolic<DT> &m) {
  //
  apply_(*this, ~m);
}

// ----------------------------------------------------------------------
// Variable Assignment Operator
//
template<typename T>
inline auto Variable::operator=(const T &rhs)
-> enable_if_string_t<T, Variable&> {
  hash_ = hash_string{}(rhs);

  return *this;
}

inline Variable &Variable::operator=(const Variable &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

// ----------------------------------------------------------------------
// Variable Member Function Definitions
//
inline hash_t Variable::hash() const {
  return hash_;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_VARIABLE_VARIABLE_HPP
