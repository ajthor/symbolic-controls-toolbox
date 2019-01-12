#ifndef SYMCTRL_MATH_SYMBOLIC_VARIABLE_VARIABLE_HPP
#define SYMCTRL_MATH_SYMBOLIC_VARIABLE_VARIABLE_HPP

// #include <memory>
#include <string>

#include <symctrl/math/expression.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/expression/symbolic.hpp>
#include <symctrl/math/symbolic/expression/unary.hpp>
#include <symctrl/shims/hash.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Symbolic Variable
//
class Variable : public Symbolic<Variable> {
public:
  using type = Variable;

  using this_type = Variable;

  using result_type = Variable;

private:
  // std::shared_ptr<BaseExpression> value_;
  // ExprUnary<Symbolic, Variable> value_;

  std::string name_;
  hash_t hash_;

public:
  explicit inline Variable(const std::string &str);

  inline Variable(const Variable &m);

  template<typename DT>
  inline Variable(const Symbolic<DT> &m);

  inline Variable &operator=(const std::string &rhs);
  inline Variable &operator=(const Variable &rhs);

  template<typename DT>
  inline Variable &operator=(const Symbolic<DT> &rhs);

  template<typename DT>
  inline Variable &operator+=(const Symbolic<DT> &rhs);
  template<typename DT>
  inline Variable &operator-=(const Symbolic<DT> &rhs);
  template<typename DT>
  inline Variable &operator*=(const Symbolic<DT> &rhs);
  template<typename DT>
  inline Variable &operator/=(const Symbolic<DT> &rhs);

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

  inline auto value() const -> const result_type&;

  inline std::string &name();
  inline const std::string &name() const;

  inline hash_t hash() const;
};

// ----------------------------------------------------------------------
// Variable Constructor
//
inline Variable::Variable(const std::string &str) {
  // value_ = std::make_shared<ExprUnary<Symbolic, Variable>>(*this);
  // value_ = ExprUnary<Symbolic, Variable>(*this);
  name_ = str;
  hash_ = hash_string{}(str);
}

inline Variable::Variable(const Variable &m) :
                          // value_(m.value_),
                          name_(m.name_),
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
inline Variable &Variable::operator=(const std::string &rhs) {
  name_ = rhs;
  hash_ = hash_string{}(rhs);

  return *this;
}

inline Variable &Variable::operator=(const Variable &rhs) {
  name_ = rhs.name();
  hash_ = rhs.hash();

  return *this;
}

template<typename DT>
inline Variable &Variable::operator=(const Symbolic<DT> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

// ----------------------------------------------------------------------
// Variable Member Function Definitions
//
inline auto Variable::value() const -> const result_type& {
  return *this;
}

inline std::string &Variable::name() {
  return name_;
}

inline const std::string &Variable::name() const {
  return name_;
}

inline hash_t Variable::hash() const {
  return hash_;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_VARIABLE_VARIABLE_HPP
