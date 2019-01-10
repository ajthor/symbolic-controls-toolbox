#ifndef SYMCTRL_MATH_EXPRESSION_MUL_HPP
#define SYMCTRL_MATH_EXPRESSION_MUL_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprMul
//
template<template<typename> class DT, typename T1, typename T2>
class ExprMul : public Expression<DT<ExprMul<DT, T1, T2>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_MUL_HPP
