#ifndef MATH_TRAITS_IS_MATRIX_HPP
#define MATH_TRAITS_IS_MATRIX_HPP

#include <type_traits>

#include <math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_matrix
//
template<template<typename> class T>
struct is_matrix : std::false_type {};

template<>
struct is_matrix<Matrix> : std::true_type {};

// ----------------------------------------------------------------------
// SFINAE is_matrix_t
//
template<class T>
struct is_matrix_helper {
private:
  template<typename ...DT>
  static std::true_type test(Matrix<DT...> &);

  template<typename ...DT>
  static std::true_type test(const Matrix<DT...> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

template<typename T>
using is_matrix_t = typename is_matrix_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_matrix_b
//
// template<template<typename> typename T>
// template<template<typename...> class T>
// struct is_matrix_b : std::is_base_of<Matrix<T>, T> {};

} // Math
} // Controls

#endif /* end of include guard: MATH_TRAITS_IS_MATRIX_HPP */
