#ifndef SYMCTRL_MATH_EXPRESSION_SUB_HPP
#define SYMCTRL_MATH_EXPRESSION_SUB_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprSub
//
template<template<typename> class DT, typename T1, typename T2>
class ExprSub : public Expression<DT<ExprSub<DT, T1, T2>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_SUB_HPP
