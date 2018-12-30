#ifndef MATH_MATRIX_CONSTANT_CONSTANT_HPP
#define MATH_MATRIX_CONSTANT_CONSTANT_HPP

#include <algorithm>

#include <math/matrix/dense/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ConstantMatrix
//
template<typename T, size_t N, size_t M>
class ConstantMatrix : public Matrix<ConstantMatrix<T, N, M>> {
private:
  const T v_;

public:
  ConstantMatrix(const T v);
  // ConstantMatrix(const std::vector<T> v);

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline std::vector<T> as_vec() const;
  inline DenseMatrix<T> as_dense() const;

  inline T operator[](const size_t pos);
  inline const T operator[](const size_t pos) const;

  inline T operator()(const size_t row, const size_t col);
  inline const T operator()(const size_t row, const size_t col) const;
};

template<typename T, size_t N, size_t M>
ConstantMatrix<T, N, M>::ConstantMatrix(const T v) : v_(v) {
  //
  // v_ = std::vector<T>(N*M, v);
}

// template<typename T, size_t N, size_t M>
// ConstantMatrix<T, N, M>::ConstantMatrix(const std::vector<T> v) : v_(v) {
//   //
// }

template<typename T, size_t N, size_t M>
inline size_t ConstantMatrix<T, N, M>::size() const {
  return N*M;
}

template<typename T, size_t N, size_t M>
inline size_t ConstantMatrix<T, N, M>::capacity() const {
  return 0;
}

template<typename T, size_t N, size_t M>
inline bool ConstantMatrix<T, N, M>::empty() const {
  return false;
}

template<typename T, size_t N, size_t M>
inline size_t ConstantMatrix<T, N, M>::nrows() const {
  return N;
}

template<typename T, size_t N, size_t M>
inline size_t ConstantMatrix<T, N, M>::ncols() const {
  return M;
}

template<typename T, size_t N, size_t M>
inline std::vector<T> ConstantMatrix<T, N, M>::as_vec() const {
  std::vector<T> v(N*M, v_);

  return v;
}

template<typename T, size_t N, size_t M>
inline DenseMatrix<T> ConstantMatrix<T, N, M>::as_dense() const {
  std::vector<T> v = (*this).as_vec();

  return DenseMatrix<T>(N, M, v);
}

template<typename T, size_t N, size_t M>
inline T ConstantMatrix<T, N, M>::operator[](const size_t pos) {
  return v_;
}

template<typename T, size_t N, size_t M>
inline const T ConstantMatrix<T, N, M>::operator[](const size_t pos) const {
  return v_;
}

template<typename T, size_t N, size_t M>
inline T ConstantMatrix<T, N, M>::operator()(const size_t row,
                                             const size_t col) {
  return v_;
}

template<typename T, size_t N, size_t M>
inline const T ConstantMatrix<T, N, M>::operator()(const size_t row,
                                                   const size_t col) const {
  return v_;
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_CONSTANT_CONSTANT_HPP */
