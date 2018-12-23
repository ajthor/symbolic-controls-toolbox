#ifndef MATH_TRAITS_IS_EXPR_HPP
#define MATH_TRAITS_IS_EXPR_HPP

#include <type_traits>

#include <math/matrix/expr.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_expr
//
template<template<typename> class T>
struct is_expr : std::false_type {};

template<>
struct is_expr<Expression> : std::true_type {};

// ----------------------------------------------------------------------
// SFINAE is_expr_t
//
template<class T>
struct is_expr_helper {
private:
  template<typename ...DT>
  static std::true_type test(Expression<DT...> &);

  template<typename ...DT>
  static std::true_type test(const Expression<DT...> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

template<class T>
using is_expr_t = typename is_expr_helper<T>::type;

} // Math
} // Controls

#endif /* end of include guard: MATH_TRAITS_IS_EXPR_HPP */
