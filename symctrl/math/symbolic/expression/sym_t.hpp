#ifndef SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_T_HPP
#define SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_T_HPP

#include <memory>
#include <string>

#include <symctrl/assert.hpp>
#include <symctrl/math/symbolic/symbolic.hpp>
#include <symctrl/math/symbolic/expression/symbolic.hpp>
#include <symctrl/math/symbolic/sym_t/sym_t.hpp>
#include <symctrl/shims/hash.hpp>
#include <symctrl/type_traits/is_numeric.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// sym_t Expressions
//
template<typename T>
inline sym_t &operator+=(sym_t &lhs, const T &rhs) {
  return lhs + rhs;
}

template<typename T>
inline sym_t &operator-=(sym_t &lhs, const T &rhs) {
  return lhs - rhs;
}

template<typename T>
inline sym_t &operator*=(sym_t &lhs, const T &rhs) {
  return lhs * rhs;
}

template<typename T>
inline sym_t &operator/=(sym_t &lhs, const T &rhs) {
  return lhs / rhs;
}

template<typename DT>
inline void sym_t::apply(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_t::apply");
  ptr_.reset();
  ptr_ = std::make_shared<Model<DT>>(~rhs);
}

template<typename DT>
inline void sym_t::apply_add(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_t::apply_add");
  // // std::cout << "tmp: " << tmp->as_str() << '\n';
  // // tmp->printType();
  // // std::cout << "rhs: " << (~rhs).as_str() << '\n';
  // // ptr_ = eval_add_(*tmp, ~rhs);
  // // ptr_->printType();
  // // std::cout << "final result: " << ptr_->as_str() << '\n';
  // // std::shared_ptr<const Concept> tmp = ptr_;
  // // ptr_ = eval_add_(*tmp, ~rhs);
  // std::cout << "symbolic type: " << typeid(std::declval<DT>()).name() << '\n';
  // std::shared_ptr<const Concept> tmp = eval_add_(*ptr_, ~rhs);
  // std::cout << "tmp: " << tmp->as_str() << '\n';
  // ptr_.swap(tmp);
  // std::cout << "ptr_: " << ptr_->as_str() << '\n';
  // ptr_->printType();
  // // ptr_.reset();
  // // ptr_ = tmp;

  std::shared_ptr<const Concept> tmp;
  ptr_.swap(tmp);
  // ptr_ = eval_add_(*tmp, ~rhs);
}

// template<typename DT>
// inline void sym_t::apply_sub(const Symbolic<DT> &rhs) {
//   SYMCTRL_DEBUG("sym_t::apply_sub");
//   // ptr_->apply_sub(~rhs);
//
// }

template<typename DT>
inline void sym_t::apply_mul(const Symbolic<DT> &rhs) {
  SYMCTRL_DEBUG("sym_t::apply_mul");
  // ptr_->apply_mul(~rhs);

  std::shared_ptr<const Concept> tmp;
  ptr_.swap(tmp);
  // ptr_ = eval_mul_(*tmp, ~rhs);
}
//
// template<typename DT>
// inline void sym_t::apply_div(const Symbolic<DT> &rhs) {
//   SYMCTRL_DEBUG("sym_t::apply_div");
//   // ptr_->apply_div(~rhs);
//
// }
//
// template<typename DT>
// inline void sym_t::apply_diff(const Symbolic<DT> &rhs) {
//   SYMCTRL_DEBUG("sym_t::apply_diff");
//   // ptr_->apply_diff(~rhs);
//
// }

// ----------------------------------------------------------------------
// sym_t equal
//
inline bool equal(const sym_t &lhs, const sym_t &rhs) {
  return lhs.hash() == rhs.hash();
}

template<typename DT>
inline bool equal(const sym_t &lhs, const Symbolic<DT> &rhs) {
  return lhs.hash() == (~rhs).hash();
}

inline bool operator==(const sym_t &lhs, const sym_t &rhs) {
  return equal(lhs, rhs);
}

template<typename DT>
inline bool operator==(const sym_t &lhs, const Symbolic<DT> &rhs) {
  return equal(lhs, ~rhs);
}

inline bool operator!=(const sym_t &lhs, const sym_t &rhs) {
  return !equal(lhs, rhs);
}

template<typename DT>
inline bool operator!=(const sym_t &lhs, const Symbolic<DT> &rhs) {
  return !equal(lhs, ~rhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_SYMBOLIC_EXPRESSION_SYM_T_HPP
