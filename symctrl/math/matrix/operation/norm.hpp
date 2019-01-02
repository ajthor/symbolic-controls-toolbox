#ifndef SYMCTRL_MATH_MATRIX_OPERATION_NORM
#define SYMCTRL_MATH_MATRIX_OPERATION_NORM

#include <algorithm>
#include <numeric>
#include <cmath>
#include <vector>

#include <symctrl/math/matrix/vector.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Vector Norm
//
template<typename T>
inline T infinity_norm(const std::vector<T> &v) {
  T largest = v[0];

  for(size_t i = 0; i < v.size(); i++) {
    if(v[i] > largest) {
      largest = v[i];
    }
  }

  return largest;
}

template<typename T>
inline T infinity_norm(const Vector<T> &v) {
  return infinity_norm(v.as_vec());
}

template<typename T>
inline double norm(const std::vector<T> &v, unsigned p = 2) {
  double current = 0;

  for(size_t i = 0; i < v.size(); i++) {
    current += std::pow(std::fabs(v[i]), p);
  }

  return std::pow(current, 1.0/p);
}

template<typename T>
inline double norm(const Vector<T> &v, unsigned p = 2) {
  return norm(v.as_vec(), p);
}

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_OPERATION_NORM */
