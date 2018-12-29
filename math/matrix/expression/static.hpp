#ifndef MATH_MATRIX_EXPRESSION_STATIC_HPP
#define MATH_MATRIX_EXPRESSION_STATIC_HPP

#include <math/assert.hpp>
#include <math/matrix/static/static.hpp>
#include <math/matrix/static/identity.hpp>
#include <math/matrix/expression/unary.hpp>
#include <math/traits/is_static.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Identity Expressions
//
template<typename T, size_t N, size_t M, typename M2>
inline auto
operator+(const IdentityMatrix<T, N, M> &lhs, const M2 rhs)
-> typename std::enable_if<std::is_scalar<M2>::value, const DenseMatrix<T>>::type {
  return DenseMatrix<T>((~lhs).as_dense() += rhs);
}

template<typename M1, typename T, size_t N, size_t M>
inline auto
operator+(const M1 lhs, const IdentityMatrix<T, N, M> &rhs)
-> typename std::enable_if<std::is_scalar<M1>::value, const DenseMatrix<T>>::type {
  return DenseMatrix<T>((~rhs).as_dense() += lhs);
}

template<typename T, size_t N, size_t M, typename M2>
inline auto
operator*(const IdentityMatrix<T, N, M> &lhs, const Matrix<M2> &rhs)
-> typename std::enable_if<N == M, const M2>::type {
  return (~rhs);
}

template<typename M1, typename T, size_t N, size_t M>
inline auto
operator*(const Matrix<M1> &lhs, const IdentityMatrix<T, N, M> &rhs)
-> typename std::enable_if<N == M, const M1>::type {
  return (~lhs);
}

template<typename T, size_t N, size_t M, typename M2>
inline auto
operator*(const IdentityMatrix<T, N, M> &lhs, const M2 rhs)
-> typename std::enable_if<std::is_scalar<M2>::value, const DenseMatrix<T>>::type {
  return DenseMatrix<T>((~lhs).as_dense() *= rhs);
}

template<typename M1, typename T, size_t N, size_t M>
inline auto
operator*(const M1 lhs, const IdentityMatrix<T, N, M> &rhs)
-> typename std::enable_if<std::is_scalar<M1>::value, const DenseMatrix<T>>::type {
  return DenseMatrix<T>((~rhs).as_dense() *= lhs);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPRESSION_STATIC_HPP */
