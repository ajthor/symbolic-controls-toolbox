#ifndef MATH_MATRIX_ASSERT_HPP
#define MATH_MATRIX_ASSERT_HPP

#include <cassert>

namespace Controls {
namespace Math {

//
#ifndef MATRIX_ASSERT
#define MATRIX_ASSERT(expr) assert(expr);
#endif

// Uncomment this line to enable debugging.
// #define MATRIX_DEBUG_OUT

#ifdef MATRIX_DEBUG_OUT
#define MATRIX_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define MATRIX_DEBUG(msg) // msg
#endif

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_ASSERT_HPP */
