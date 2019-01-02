#ifndef SYMCTRL_TRAITS_IS_EXPR_HPP
#define SYMCTRL_TRAITS_IS_EXPR_HPP

#include <type_traits>

#include <symctrl/math/matrix/expression/expression.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_expr_helper
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

// ----------------------------------------------------------------------
// SFINAE is_expr_t
//
template<class T>
using is_expr_t = typename is_expr_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_expr
//
template<typename T>
struct is_expr : is_expr_t<T>::type {};

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_TRAITS_IS_EXPR_HPP */