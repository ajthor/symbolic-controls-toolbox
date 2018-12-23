#ifndef MATH_TRAITS_IS_VECTOR_HPP
#define MATH_TRAITS_IS_VECTOR_HPP

#include <type_traits>

#include <math/matrix/vector.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_vector
//
template<template<typename> class T>
struct is_vector : std::false_type {};

template<>
struct is_vector<Vector> : std::true_type {};

// ----------------------------------------------------------------------
// SFINAE is_vector_t
//
template<class T>
struct is_vector_helper {
private:
  template<typename ...DT>
  static std::true_type test(Vector<DT...> &);

  template<typename ...DT>
  static std::true_type test(const Vector<DT...> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

template<typename T>
using is_vector_t = typename is_vector_helper<T>::type;

} // Math
} // Controls

#endif /* end of include guard: MATH_TRAITS_IS_VECTOR_HPP */
