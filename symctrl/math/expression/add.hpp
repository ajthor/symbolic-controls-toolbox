#ifndef SYMCTRL_MATH_EXPRESSION_ADD_HPP
#define SYMCTRL_MATH_EXPRESSION_ADD_HPP

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprAdd
//
template<template<typename> class DT, typename T1, typename T2>
class ExprAdd : public Expression<DT<ExprAdd<DT, T1, T2>>> {};

} // Math
} // Controls

#endif // SYMCTRL_MATH_EXPRESSION_ADD_HPP
