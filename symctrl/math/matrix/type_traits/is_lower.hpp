#ifndef SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_LOWER_HPP
#define SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_LOWER_HPP

#include <symctrl/type_traits/is_default.hpp>
#include <symctrl/math/matrix/matrix.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// is_lower
//
template<typename DT>
bool is_lower(const Matrix<DT> &m) {
  if((~m).nrows() != (~m).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~m).nrows(); i++) {
    for(size_t j = 0; j < (~m).ncols(); j++) {
      // If the element is above the diagonal, make sure it is the default.
      if(i < j) {
        if(!is_default((~m)(i, j))) {
          return false;
        }
      }
    }
  }

  return true;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_TYPE_TRAITS_IS_LOWER_HPP
