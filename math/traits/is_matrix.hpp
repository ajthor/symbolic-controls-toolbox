#ifndef MATH_TRAITS_IS_MATRIX_HPP
#define MATH_TRAITS_IS_MATRIX_HPP

#include <type_traits>

#include <math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_matrix_helper
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

// ----------------------------------------------------------------------
// SFINAE is_matrix_t
//
template<typename T>
using is_matrix_t = typename is_matrix_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_matrix
//
template<typename T>
struct is_matrix : is_matrix_t<T>::type {};

} // Math
} // Controls

#endif /* end of include guard: MATH_TRAITS_IS_MATRIX_HPP */
