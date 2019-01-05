#ifndef SYMCTRL_TRAITS_IS_SYMBOLIC_HPP
#define SYMCTRL_TRAITS_IS_SYMBOLIC_HPP

#include <type_traits>

#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// SFINAE is_symbolic_helper
//
template<class T>
struct is_symbolic_helper {
private:
  template<template<typename> class DT>
  static std::true_type test(DT<symbolic_t> &);

  template<template<typename> class DT>
  static std::true_type test(const DT<symbolic_t> &);

  template<template<typename> class DT>
  static std::true_type test(DT<symbolic_integer_t> &);

  template<template<typename> class DT>
  static std::true_type test(const DT<symbolic_integer_t> &);

  template<template<typename> class DT>
  static std::true_type test(DT<symbolic_symbol_t> &);

  template<template<typename> class DT>
  static std::true_type test(const DT<symbolic_symbol_t> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

// ----------------------------------------------------------------------
// SFINAE is_symbolic_t
//
template<class T>
using is_symbolic_t = typename is_symbolic_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_symbolic
//
template<typename T>
struct is_symbolic : is_symbolic_t<T>::type {};

// ----------------------------------------------------------------------
// SFINAE enable_if_symbolic
//
template<typename T, typename R = void>
struct enable_if_symbolic : std::enable_if<is_symbolic<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE enable_if_symbolic_t
//
template<typename T, typename R = void>
using enable_if_symbolic_t = typename enable_if_symbolic<T, R>::type;

} // Controls

#endif // SYMCTRL_TRAITS_IS_SYMBOLIC_HPP
