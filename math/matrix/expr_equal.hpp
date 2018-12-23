#ifndef MATH_MATRIX_EXPR_EQUAL_HPP
#define MATH_MATRIX_EXPR_EQUAL_HPP

#include <symengine/basic.h>

#include "assert.h"
#include "matrix.hpp"
#include "dense.hpp"
#include "dense_sym.hpp"
#include "vector.hpp"
#include "vector_sym.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Matrix Equal
//
template<typename D1, typename D2>
inline bool equal(const Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  return is_equal(~lhs, ~rhs);
}

// ----------------------------------------------------------------------
// DenseMatrix Equal
//
template<typename T>
inline bool equal(const DenseMatrix<T> &lhs, const DenseMatrix<T> &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~lhs).nrows(); i++) {
    for(size_t j = 0; j < (~lhs).ncols(); j++) {
      if((~lhs)(i, j) != (~rhs)(i, j))
        return false;
    }
  }

  return true;
}

template<>
inline bool equal(const SymbolicMatrix &lhs, const SymbolicMatrix &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~lhs).nrows(); i++) {
    for(size_t j = 0; j < (~lhs).ncols(); j++) {
      if(!eq(*(~lhs)(i, j), *(~rhs)(i, j)))
        return false;
    }
  }

  return true;
}

// ----------------------------------------------------------------------
// Vector Equal
//
template<typename T>
inline bool equal(const Vector<T> &lhs, const Vector<T> &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~lhs).size(); i++) {
    if((~lhs)[i] != (~rhs)[i])
      return false;
  }

  return true;
}

template<>
inline bool equal(const SymbolicVector &lhs, const SymbolicVector &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~lhs).size(); i++) {
    if(!eq(*(~lhs)[i], *(~rhs)[i]))
      return false;
  }

  return true;
}

// ----------------------------------------------------------------------
// Equality Operator
//
template<typename D1, typename D2>
inline bool operator==(const Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  return equal(~lhs, ~rhs);
}

template<typename D1, typename D2>
inline bool operator!=(const Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  return !equal(~lhs, ~rhs);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_EXPR_EQUAL_HPP */
