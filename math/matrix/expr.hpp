#ifndef MATH_MATRIX_EXPR_HPP
#define MATH_MATRIX_EXPR_HPP

#include <type_traits>

#include "matrix.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Expression
//
template<typename DT>
class Expression : public DT {};

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_HPP */
