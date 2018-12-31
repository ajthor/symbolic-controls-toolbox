#ifndef SYMCTRL_TRAITS_IS_SYMBOLIC_HPP
#define SYMCTRL_TRAITS_IS_SYMBOLIC_HPP

#include <type_traits>

#include <symengine/basic.h>
#include <symengine/integer.h>
#include <symengine/symbol.h>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_symbolic_helper
//
template<class T>
struct is_symbolic_helper {
private:
  using RCPBasic = SymEngine::RCP<const SymEngine::Basic>;
  using RCPInteger = SymEngine::RCP<const SymEngine::Integer>;
  using RCPSymbol = SymEngine::RCP<const SymEngine::Symbol>;

  template<template<typename> class DT>
  static std::true_type test(DT<RCPBasic> &);

  template<template<typename> class DT>
  static std::true_type test(const DT<RCPBasic> &);

  template<template<typename> class DT>
  static std::true_type test(DT<RCPInteger> &);

  template<template<typename> class DT>
  static std::true_type test(const DT<RCPInteger> &);

  template<template<typename> class DT>
  static std::true_type test(DT<RCPSymbol> &);

  template<template<typename> class DT>
  static std::true_type test(const DT<RCPSymbol> &);

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

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_TRAITS_IS_SYMBOLIC_HPP */
