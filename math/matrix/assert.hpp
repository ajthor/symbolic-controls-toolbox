#ifndef MATH_ASSERT_HPP
#define MATH_ASSERT_HPP

#include <cassert>

namespace Controls {
namespace Math {

//
#ifndef MATRIX_ASSERT
#define MATRIX_ASSERT(expr) assert(expr);
#endif

} // Math
} // Controls

#endif /* end of include guard: MATH_ASSERT_HPP */
