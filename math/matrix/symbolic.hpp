#ifndef MATH_MATRIX_SYMBOLIC_HPP
#define MATH_MATRIX_SYMBOLIC_HPP

#include <symengine/add.h>
#include <symengine/mul.h>
#include <symengine/basic.h>
#include <symengine/constants.h>

namespace Controls {
namespace Math {

using RCPBasic = SymEngine::RCP<const SymEngine::Basic>;

// ----------------------------------------------------------------------
// equal
//
template<>
inline bool equal(const RCPBasic lhs, const RCPBasic rhs) {
  return SymEngine::eq(*lhs, *rhs);
}

template<>
inline bool is_default(const RCPBasic v) {
  return SymEngine::eq(*v, *SymEngine::zero);
}

// ----------------------------------------------------------------------
// ExprAdd Symbolic Add Scalar Operator
//
template<typename M1, typename M2>
inline auto
operator+(const Matrix<M1> lhs, const M2 &rhs) -> typename std::enable_if<std::is_same<M2, RCPBasic>::value, const ExprUnary<M1>>::type {
  M1 tmp(~lhs);
  return ExprUnary<M1>(tmp += rhs);
}

template<typename M1, typename M2>
inline auto
operator+(const M1 lhs, const Matrix<M2> &rhs) -> typename std::enable_if<std::is_same<M1, RCPBasic>::value, const ExprUnary<M2>>::type {
  M2 tmp(~rhs);
  return ExprUnary<M2>(tmp += lhs);
}

// ----------------------------------------------------------------------
// ExprAdd Symbolic Sub Scalar Operator
//
template<typename M1, typename M2>
inline auto
operator-(const Matrix<M1> lhs, const M2 &rhs) -> typename std::enable_if<std::is_same<M2, RCPBasic>::value, const ExprUnary<M1>>::type {
  M1 tmp(~lhs);
  return ExprUnary<M1>(tmp -= rhs);
}

template<typename M1, typename M2>
inline auto
operator-(const M1 lhs, const Matrix<M2> &rhs) -> typename std::enable_if<std::is_same<M1, RCPBasic>::value, const ExprUnary<M2>>::type {
  M2 tmp(~rhs);
  return ExprUnary<M2>(tmp -= lhs);
}

// ----------------------------------------------------------------------
// ExprMul Symbolic Multiply Scalar Operator
//
template<typename M1, typename M2>
inline auto
operator*(const Matrix<M1> lhs, const M2 &rhs) -> typename std::enable_if<std::is_same<M2, RCPBasic>::value, const ExprUnary<M1>>::type {
  M1 tmp(~lhs);
  return ExprUnary<M1>(tmp *= rhs);
}

template<typename M1, typename M2>
inline auto
operator*(const M1 lhs, const Matrix<M2> &rhs) -> typename std::enable_if<std::is_same<M1, RCPBasic>::value, const ExprUnary<M2>>::type {
  M2 tmp(~rhs);
  return ExprUnary<M2>(tmp *= lhs);
}

// ----------------------------------------------------------------------
// ExprMul Symbolic Divide Scalar Operator
//
template<typename M1, typename M2>
inline auto
operator/(const Matrix<M1> lhs, const M2 &rhs) -> typename std::enable_if<std::is_same<M2, RCPBasic>::value, const ExprUnary<M1>>::type {
  M1 tmp(~lhs);
  return ExprUnary<M1>(tmp /= rhs);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_SYMBOLIC_HPP */
