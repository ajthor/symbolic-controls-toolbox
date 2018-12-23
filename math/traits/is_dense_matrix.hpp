#ifndef MATH_TRAITS_IS_DENSE_MATRIX_HPP
#define MATH_TRAITS_IS_DENSE_MATRIX_HPP

#include <type_traits>

#include <math/matrix/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_dense_matrix
//
template<template<typename> class T>
struct is_dense_matrix : std::false_type {};

template<>
struct is_dense_matrix<DenseMatrix> : std::true_type {};

// ----------------------------------------------------------------------
// SFINAE is_dense_matrix_t
//
template<class T>
struct is_dense_matrix_helper {
private:
  template<typename ...DT>
  static std::true_type test(DenseMatrix<DT...> &);

  template<typename ...DT>
  static std::true_type test(const DenseMatrix<DT...> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

template<typename T>
using is_dense_matrix_t = typename is_dense_matrix_helper<T>::type;

} // Math
} // Controls

#endif /* end of include guard: MATH_TRAITS_IS_DENSE_MATRIX_HPP */
