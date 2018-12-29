#ifndef MATH_MATRIX_ASSERT_HPP
#define MATH_MATRIX_ASSERT_HPP

#include <cassert>

namespace Controls {
namespace Math {

//
#ifndef MATH_ASSERT
#define MATH_ASSERT(expr) assert(expr);
#endif

// Uncomment this line to enable debugging.
// #define MATH_DEBUG_OUT

#ifdef MATH_DEBUG_OUT
#define MATH_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define MATH_DEBUG(msg) // msg
#endif

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_ASSERT_HPP */
