#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_CONSTANT_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_CONSTANT_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/static.hpp>
#include <symctrl/math/matrix/constant/identity.hpp>
#include <symctrl/math/matrix/constant/ones.hpp>
#include <symctrl/math/matrix/constant/zeros.hpp>
#include <symctrl/math/matrix/expression/unary.hpp>
#include <symctrl/traits/is_scalar.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ConstantMatrix Expressions
//
template<typename T, size_t N, size_t M, T C, typename M2>
inline auto
operator+(const ConstantMatrix<T, N, M, C> &lhs, const M2 rhs)
-> enable_if_scalar_t<M2, const ConstantMatrix<T, N, M, C + rhs>> {
  return ConstantMatrix<T, N, M, C + rhs>();
}

template<typename M1, typename T, size_t N, size_t M, T C>
inline auto
operator+(const M1 lhs, const ConstantMatrix<T, N, M, C> &rhs)
-> enable_if_scalar_t<M1, const ConstantMatrix<T, N, M, C + lhs>> {
  return ConstantMatrix<T, N, M, C + lhs>();
}

template<typename T, size_t N, size_t M, T C, typename M2>
inline auto
operator*(const ConstantMatrix<T, N, M, C> &lhs, const M2 rhs)
-> enable_if_scalar_t<M2, const ConstantMatrix<T, N, M, C * rhs>> {
  return ConstantMatrix<T, N, M, C * rhs>();
}

template<typename M1, typename T, size_t N, size_t M, T C>
inline auto
operator*(const M1 lhs, const ConstantMatrix<T, N, M, C> &rhs)
-> enable_if_scalar_t<M1, const ConstantMatrix<T, N, M, C * lhs>> {
  return ConstantMatrix<T, N, M, C * lhs>();
}

// ----------------------------------------------------------------------
// ConstantMatrix Equal
//
template<typename T, size_t N, size_t M, T C>
inline bool equal(const ConstantMatrix<T, N, M, C> &lhs,
                  const ConstantMatrix<T, N, M, C> &rhs) {
  return true;
}

template<typename DT, typename T, size_t N, size_t M, T C>
inline bool equal(const Matrix<DT> &lhs,
                  const ConstantMatrix<T, N, M, C> &rhs) {
  if((~lhs).nrows() != N || (~lhs).ncols() != M) {
    return false;
  }

  for(size_t i = 0; i < (~rhs).size(); i++) {
    if(!equal((~lhs)[i], (~rhs)[i]))
      return false;
  }

  return true;
}

// template<typename DT, typename T, size_t N, size_t M, T C>
// inline bool equal(const ConstantMatrix<T, N, M, C> &lhs,
//                   const Matrix<DT> &rhs) {
//   return equal(~rhs, ~lhs);
// }

// ----------------------------------------------------------------------
// Identity Expressions
//
template<typename T, size_t N, size_t M, typename M2>
inline auto
operator+(const Identity<T, N, M> &lhs, const M2 rhs)
-> enable_if_scalar_t<M2, const StaticDense<T, N, M>> {
  return StaticDense<T, N, M>((~lhs).as_dense() += rhs);
}

template<typename M1, typename T, size_t N, size_t M>
inline auto
operator+(const M1 lhs, const Identity<T, N, M> &rhs)
-> enable_if_scalar_t<M1, const StaticDense<T, N, M>> {
  return StaticDense<T, N, M>((~rhs).as_dense() += lhs);
}

template<typename T, size_t N, size_t M, typename M2>
inline auto
operator*(const Identity<T, N, M> &lhs, const M2 rhs)
-> enable_if_scalar_t<M2, const StaticDense<T, N, M>> {
  return StaticDense<T, N, M>((~lhs).as_dense() *= rhs);
}

template<typename M1, typename T, size_t N, size_t M>
inline auto
operator*(const M1 lhs, const Identity<T, N, M> &rhs)
-> enable_if_scalar_t<M1, const StaticDense<T, N, M>> {
  return StaticDense<T, N, M>((~rhs).as_dense() *= lhs);
}

template<typename T, size_t N, size_t M, typename M2>
inline auto
operator*(const Identity<T, N, M> &lhs, const Matrix<M2> &rhs)
-> typename std::enable_if<N == M, const M2>::type {
  return (~rhs);
}

template<typename M1, typename T, size_t N, size_t M>
inline auto
operator*(const Matrix<M1> &lhs, const Identity<T, N, M> &rhs)
-> typename std::enable_if<N == M, const M1>::type {
  return (~lhs);
}

template<typename T, size_t N, size_t M>
inline auto
operator*(const Identity<T, N, M> &lhs, const Identity<T, N, M> &rhs)
-> typename std::enable_if<N == M, const Identity<T, N, M>>::type {
  return (~lhs);
}

// ----------------------------------------------------------------------
// Identity Equal
//
template<typename T, size_t N, size_t M>
inline bool equal(const Identity<T, N, M> &lhs,
                  const Identity<T, N, M> &rhs) {
  return true;
}

template<typename DT, typename T, size_t N, size_t M>
inline bool equal(const Matrix<DT> &lhs, const Identity<T, N, M> &rhs) {
  if((~lhs).nrows() != N || (~lhs).ncols() != M) {
    return false;
  }

  for(size_t i = 0; i < (~rhs).size(); i++) {
    if(!equal((~lhs)[i], (~rhs)[i]))
      return false;
  }

  return true;
}

// template<typename DT, typename T, size_t N, size_t M>
// inline bool equal(const Identity<T, N, M> &lhs, const Matrix<DT> &rhs) {
//   return equal(~rhs, ~lhs);
// }

// ----------------------------------------------------------------------
// Ones Expressions
//
template<typename T, size_t N, size_t M, typename M2>
inline auto
operator+(const Ones<T, N, M> &lhs, const M2 rhs)
-> enable_if_scalar_t<M2, const StaticDense<T, N, M>> {
  return StaticDense<T, N, M>((~lhs).as_dense() += rhs);
}

template<typename M1, typename T, size_t N, size_t M>
inline auto
operator+(const M1 lhs, const Ones<T, N, M> &rhs)
-> enable_if_scalar_t<M1, const StaticDense<T, N, M>> {
  return StaticDense<T, N, M>((~rhs).as_dense() += lhs);
}

template<typename T, size_t N, size_t M, typename M2>
inline auto
operator*(const Ones<T, N, M> &lhs, const M2 rhs)
-> enable_if_scalar_t<M2, const StaticDense<T, N, M>> {
  return StaticDense<T, N, M>((~lhs).as_dense() *= rhs);
}

template<typename M1, typename T, size_t N, size_t M>
inline auto
operator*(const M1 lhs, const Ones<T, N, M> &rhs)
-> enable_if_scalar_t<M1, const StaticDense<T, N, M>> {
  return StaticDense<T, N, M>((~rhs).as_dense() *= lhs);
}

// ----------------------------------------------------------------------
// Ones Equal
//
template<typename T, size_t N, size_t M>
inline bool equal(const Ones<T, N, M> &lhs,
                  const Ones<T, N, M> &rhs) {
  return true;
}

template<typename DT, typename T, size_t N, size_t M>
inline bool equal(const Matrix<DT> &lhs, const Ones<T, N, M> &rhs) {
  if((~lhs).nrows() != N || (~lhs).ncols() != M) {
    return false;
  }

  for(size_t i = 0; i < (~rhs).size(); i++) {
    if(!equal((~lhs)[i], (~rhs)[i]))
      return false;
  }

  return true;
}

// template<typename DT, typename T, size_t N, size_t M>
// inline bool equal(const Ones<T, N, M> &lhs, const Matrix<DT> &rhs) {
//   return equal(~rhs, ~lhs);
// }

// ----------------------------------------------------------------------
// Zeros Expressions
//
template<typename T, size_t N, size_t M, typename M2>
inline auto
operator+(const Zeros<T, N, M> &lhs, const M2 rhs)
-> enable_if_scalar_t<M2, const StaticDense<T, N, M>> {
  return StaticDense<T, N, M>((~lhs).as_dense() += rhs);
}

template<typename M1, typename T, size_t N, size_t M>
inline auto
operator+(const M1 lhs, const Zeros<T, N, M> &rhs)
-> enable_if_scalar_t<M1, const StaticDense<T, N, M>> {
  return StaticDense<T, N, M>((~rhs).as_dense() += lhs);
}

template<typename T, size_t N, size_t M, typename M2>
inline auto
operator*(const Zeros<T, N, M> &lhs, const M2 rhs)
-> enable_if_scalar_t<M2, const Zeros<T, N, M>> {
  return ~lhs;
}

template<typename M1, typename T, size_t N, size_t M>
inline auto
operator*(const M1 lhs, const Zeros<T, N, M> &rhs)
-> enable_if_scalar_t<M1, const Zeros<T, N, M>> {
  return ~rhs;
}

// ----------------------------------------------------------------------
// Zeros Equal
//
template<typename T, size_t N, size_t M>
inline bool equal(const Zeros<T, N, M> &lhs,
                  const Zeros<T, N, M> &rhs) {
  return true;
}

template<typename DT, typename T, size_t N, size_t M>
inline bool equal(const Matrix<DT> &lhs, const Zeros<T, N, M> &rhs) {
  if((~lhs).nrows() != N || (~lhs).ncols() != M) {
    return false;
  }

  for(size_t i = 0; i < (~rhs).size(); i++) {
    if(!equal((~lhs)[i], (~rhs)[i]))
      return false;
  }

  return true;
}

// template<typename DT, typename T, size_t N, size_t M>
// inline bool equal(const Zeros<T, N, M> &lhs, const Matrix<DT> &rhs) {
//   return equal(~rhs, ~lhs);
// }


} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_EXPRESSION_CONSTANT_HPP */
