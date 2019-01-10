#ifndef SYMCTRL_MATH_EXPRESSION_NEG_HPP
#define SYMCTRL_MATH_EXPRESSION_NEG_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprNeg
//
template<template<typename> class DT, typename T>
class ExprNeg : public Expression<DT<ExprNeg<DT, T>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_NEG_HPP
