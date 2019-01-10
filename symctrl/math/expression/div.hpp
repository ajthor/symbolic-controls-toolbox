#ifndef SYMCTRL_MATH_EXPRESSION_DIV_HPP
#define SYMCTRL_MATH_EXPRESSION_DIV_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprDiv
//
template<template<typename> class DT, typename T1, typename T2>
class ExprDiv : public Expression<DT<ExprDiv<DT, T1, T2>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_DIV_HPP
