#ifndef SYMCTRL_TRAITS_IS_DENSE_HPP
#define SYMCTRL_TRAITS_IS_DENSE_HPP

#include <type_traits>

#include <symctrl/math/matrix/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// SFINAE is_dense_helper
//
template<class T>
struct is_dense_helper {
private:
  template<typename ...DT>
  static std::true_type test(DenseMatrix<DT...> &);

  template<typename ...DT>
  static std::true_type test(const DenseMatrix<DT...> &);

  static std::false_type test(...);

public:
  using type = decltype(test(std::declval<T&>()));
};

// ----------------------------------------------------------------------
// SFINAE is_dense_t
//
template<typename T>
using is_dense_t = typename is_dense_helper<T>::type;

// ----------------------------------------------------------------------
// SFINAE is_dense
//
template<typename T>
struct is_dense : is_dense_t<T>::type {};

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_TRAITS_IS_DENSE_HPP */