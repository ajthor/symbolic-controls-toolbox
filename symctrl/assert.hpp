#ifndef SYMCTRL_ASSERT_HPP
#define SYMCTRL_ASSERT_HPP

#include <cassert>

namespace Controls {
namespace Math {

//
#ifndef SYMCTRL_ASSERT
#define SYMCTRL_ASSERT(expr) assert(expr);
#endif

// Uncomment this line to enable debugging.
// #define SYMCTRL_DEBUG_OUT

#ifdef SYMCTRL_DEBUG_OUT
#define SYMCTRL_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define SYMCTRL_DEBUG(msg) // msg
#endif

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_ASSERT_HPP */
