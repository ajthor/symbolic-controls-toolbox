#ifndef SYMCTRL_MATH_MATRIX_CONSTANT_CONSTANT_HPP
#define SYMCTRL_MATH_MATRIX_CONSTANT_CONSTANT_HPP

#include <vector>

#include <symctrl/math/matrix/dense/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ConstantMatrix
//
template<typename T, size_t N, size_t M, T v_>
class ConstantMatrix : public Matrix<ConstantMatrix<T, N, M, v_>> {
public:
  using type = T;

private:

public:
  ConstantMatrix();

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

template<typename T, size_t N, size_t M, T v_>
ConstantMatrix<T, N, M, v_>::ConstantMatrix() {
  //
}

template<typename T, size_t N, size_t M, T v_>
inline size_t ConstantMatrix<T, N, M, v_>::size() const {
  return N*M;
}

template<typename T, size_t N, size_t M, T v_>
inline size_t ConstantMatrix<T, N, M, v_>::capacity() const {
  return 0;
}

template<typename T, size_t N, size_t M, T v_>
inline bool ConstantMatrix<T, N, M, v_>::empty() const {
  return false;
}

template<typename T, size_t N, size_t M, T v_>
inline size_t ConstantMatrix<T, N, M, v_>::nrows() const {
  return N;
}

template<typename T, size_t N, size_t M, T v_>
inline size_t ConstantMatrix<T, N, M, v_>::ncols() const {
  return M;
}

template<typename T, size_t N, size_t M, T v_>
inline std::vector<T> ConstantMatrix<T, N, M, v_>::as_vec() const {
  std::vector<T> v(N*M, v_);

  return v;
}

template<typename T, size_t N, size_t M, T v_>
inline DenseMatrix<T> ConstantMatrix<T, N, M, v_>::as_dense() const {
  std::vector<T> v = (*this).as_vec();

  return DenseMatrix<T>(N, M, v);
}

template<typename T, size_t N, size_t M, T v_>
inline T ConstantMatrix<T, N, M, v_>::operator[](const size_t pos) {
  return v_;
}

template<typename T, size_t N, size_t M, T v_>
inline const T ConstantMatrix<T, N, M, v_>::operator[](const size_t pos) const {
  return v_;
}

template<typename T, size_t N, size_t M, T v_>
inline T ConstantMatrix<T, N, M, v_>::operator()(const size_t row,
                                             const size_t col) {
  return v_;
}

template<typename T, size_t N, size_t M, T v_>
inline const T ConstantMatrix<T, N, M, v_>::operator()(const size_t row,
                                                   const size_t col) const {
  return v_;
}

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_CONSTANT_CONSTANT_HPP */
