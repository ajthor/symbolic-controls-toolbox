#ifndef SYMCTRL_TRAITS_IS_VECTOR_HPP
#define SYMCTRL_TRAITS_IS_VECTOR_HPP

#include <type_traits>

#include <symctrl/math/matrix/vector.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_vector_helper
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

// ----------------------------------------------------------------------
// SFINAE is_vector_t
//
template<typename T>
using is_vector_t = typename is_vector_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_vector
//
template<typename T>
struct is_vector : is_vector_t<T>::type {};

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_TRAITS_IS_VECTOR_HPP */
