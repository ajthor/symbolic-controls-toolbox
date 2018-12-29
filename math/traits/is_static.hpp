#ifndef MATH_TRAITS_IS_STATIC_HPP
#define MATH_TRAITS_IS_STATIC_HPP

#include <type_traits>

#include <math/matrix/static.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_static_helper
//
template<class T>
struct is_static_helper {
private:
  template<typename DT, size_t N, size_t M>
  static std::true_type test(StaticMatrix<DT, N, M> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(const StaticMatrix<DT, N, M> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(IdentityMatrix<DT, N, M> &);

  template<typename DT, size_t N, size_t M>
  static std::true_type test(const IdentityMatrix<DT, N, M> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

// ----------------------------------------------------------------------
// SFINAE is_static_t
//
template<typename T>
using is_static_t = typename is_static_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_static
//
template<typename T>
struct is_static : is_static_t<T>::type {};


} // Math
} // Controls

#endif /* end of include guard: MATH_TRAITS_IS_STATIC_HPP */
