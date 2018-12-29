#ifndef MATH_MATRIX_SPARSE_HPP
#define MATH_MATRIX_SPARSE_HPP

#include <type_traits>

#include <math/matrix/sparse/sparse.hpp>
#include <math/matrix/sparse/identity.hpp>
#include <math/matrix/expression/sparse.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// NNZ
//


// ----------------------------------------------------------------------
// Compress
//
template<size_t n, size_t m, typename T, typename DT>
inline auto compress(const Matrix<DT> &m)
-> std::enable_if<(nnz(m) < (m*(n - 1) - 1)/2), SparseMatrix<T>>::type {
  SparseMatrix<T>(n, m, m.as_vec());
}

template<size_t n, size_t m, typename T, typename DT>
inline auto compress(const Matrix<DT> &m)
-> std::enable_if<(nnz(m) >= (m*(n - 1) - 1)/2), SparseMatrix<T>>::type {
  return m;
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_SPARSE_HPP */
