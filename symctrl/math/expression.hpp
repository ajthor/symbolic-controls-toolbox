#ifndef SYMCTRL_MATH_EXPRESSION_HPP
#define SYMCTRL_MATH_EXPRESSION_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// BaseExpression
//
struct BaseExpression {};

// ----------------------------------------------------------------------
// Expression
//
template<typename DT>
class Expression : public DT, public BaseExpression {};

// ----------------------------------------------------------------------
// result_type_t
//
template<typename T>
using result_type_t = typename T::result_type;

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_HPP
