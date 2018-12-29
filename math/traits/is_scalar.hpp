#ifndef MATH_TRAITS_IS_SCALAR_HPP
#define MATH_TRAITS_IS_SCALAR_HPP

#include <type_traits>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// is_scalar_t
//
template<typename T>
using is_scalar_t = typename std::is_arithmetic<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_scalar
//
template<typename T>
struct is_scalar : is_scalar_t<T>::type {};

// ----------------------------------------------------------------------
// SFINAE enable_if_scalar
//
template<typename T, typename R = void>
struct enable_if_scalar : std::enable_if<is_scalar<T>::value, R> {};

// ----------------------------------------------------------------------
// SFINAE enable_if_scalar_t
//
template<typename T, typename R = void>
using enable_if_scalar_t = typename enable_if_scalar<T, R>::type;

} // Math
} // Controls

#endif /* end of include guard: MATH_TRAITS_IS_SCALAR_HPP */
