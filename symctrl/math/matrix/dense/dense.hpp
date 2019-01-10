#ifndef SYMCTRL_MATH_MATRIX_DENSE_DENSE_HPP
#define SYMCTRL_MATH_MATRIX_DENSE_DENSE_HPP

#include <algorithm>
#include <vector>

#include <symctrl/assert.hpp>
#include <symctrl/shims/default.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/vector.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// DenseMatrix
//
template<typename T>
class DenseMatrix : public Matrix<DenseMatrix<T>> {
public:
  using type = T;

  using result_type = DenseMatrix<T>;

private:
  size_t n_;
  size_t m_;

  std::vector<T> v_;

public:
  explicit inline DenseMatrix();
  explicit inline DenseMatrix(const size_t nrows,
                              const size_t ncols);
  explicit inline DenseMatrix(const size_t nrows,
                              const size_t ncols,
                              const std::vector<T> v);

  inline DenseMatrix(const DenseMatrix<T> &m);

  template<typename DT>
  inline DenseMatrix(const Matrix<DT> &m);

  inline DenseMatrix<T> &operator=(const T &rhs);
  inline DenseMatrix<T> &operator=(const DenseMatrix<T> &rhs);

  template<typename DT>
  inline DenseMatrix<T> &operator=(const Matrix<DT> &rhs);

  inline DenseMatrix<T> &operator+=(const T &rhs);
  inline DenseMatrix<T> &operator-=(const T &rhs);
  inline DenseMatrix<T> &operator*=(const T &rhs);
  inline DenseMatrix<T> &operator/=(const T &rhs);

  template<typename DT>
  inline void apply(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_add(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_sub(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_mul(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_inverse(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_transpose(const Matrix<DT> &rhs);

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline typename std::vector<T>::iterator begin();
  inline typename std::vector<T>::iterator end();
  inline typename std::vector<T>::const_iterator begin() const;
  inline typename std::vector<T>::const_iterator end() const;
  inline typename std::vector<T>::const_iterator cbegin() const;
  inline typename std::vector<T>::const_iterator cend() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline std::vector<T> as_vec() const;

  Vector<T> row(const size_t n) const;
  Vector<T> col(const size_t n) const;

  void swap_row(const size_t row1, const size_t row2);
  void swap_col(const size_t col1, const size_t col2);

  inline T &operator[](const size_t pos);
  inline const T &operator[](const size_t pos) const;

  inline T &operator()(const size_t row, const size_t col);
  inline const T &operator()(const size_t row, const size_t col) const;

  inline DenseMatrix<T> &inverse();
  inline DenseMatrix<T> &transpose();
};

// ----------------------------------------------------------------------
// DenseMatrix Constructor
//
template<typename T>
inline DenseMatrix<T>::DenseMatrix() :
                                   n_(0),
                                   m_(0) {
  //
  v_ = std::vector<T>(0);
}

template<typename T>
inline DenseMatrix<T>::DenseMatrix(const size_t nrows,
                                   const size_t ncols) :
                                   n_(nrows),
                                   m_(ncols) {
  //
  v_ = std::vector<T>(nrows*ncols, default_value<T>());
}

template<typename T>
inline DenseMatrix<T>::DenseMatrix(const size_t nrows,
                                   const size_t ncols,
                                   const std::vector<T> v) :
                                   n_(nrows),
                                   m_(ncols),
                                   v_(v) {
  //
}

template<typename T>
inline DenseMatrix<T>::DenseMatrix(const DenseMatrix<T> &m) :
                                   n_(m.n_),
                                   m_(m.m_),
                                   v_(m.v_) {
  //
}

template<typename T>
template<typename DT>
inline DenseMatrix<T>::DenseMatrix(const Matrix<DT> &m) :
                                   n_((~m).nrows()),
                                   m_((~m).ncols()) {
  //
  apply_(*this, ~m);
}

// ----------------------------------------------------------------------
// DenseMatrix Assignment Operator
//
template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = rhs;
  }

  return *this;
}

template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator=(const DenseMatrix<T> &rhs) {
  n_ = rhs.n_;
  m_ = rhs.m_;
  v_ = rhs.v_;

  return *this;
}

template<typename T>
template<typename DT>
inline DenseMatrix<T> &DenseMatrix<T>::operator=(const Matrix<DT> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

// ----------------------------------------------------------------------
// DenseMatrix Member Function Definitions
//
template<typename T>
inline size_t DenseMatrix<T>::size() const {
  return v_.size();
}

template<typename T>
inline size_t DenseMatrix<T>::capacity() const {
  return v_.capacity();
}

template<typename T>
inline bool DenseMatrix<T>::empty() const {
  return v_.empty();
}

template<typename T>
inline typename std::vector<T>::iterator
DenseMatrix<T>::begin() {
  return v_.begin();
}

template<typename T>
inline typename std::vector<T>::iterator
DenseMatrix<T>::end() {
  return v_.end();
}

template<typename T>
inline typename std::vector<T>::const_iterator
DenseMatrix<T>::begin() const {
  return v_.begin();
}

template<typename T>
inline typename std::vector<T>::const_iterator
DenseMatrix<T>::end() const {
  return v_.end();
}

template<typename T>
inline typename std::vector<T>::const_iterator
DenseMatrix<T>::cbegin() const {
  return v_.cbegin();
}

template<typename T>
inline typename std::vector<T>::const_iterator
DenseMatrix<T>::cend() const {
  return v_.cend();
}

template<typename T>
inline size_t DenseMatrix<T>::nrows() const {
  return n_;
}

template<typename T>
inline size_t DenseMatrix<T>::ncols() const {
  return m_;
}

template<typename T>
inline std::vector<T> DenseMatrix<T>::as_vec() const {
  return v_;
}

template<typename T>
Vector<T> DenseMatrix<T>::row(const size_t n) const {
  std::vector<T> result(m_);
  for(size_t i = 0; i < m_; i++) {
    result[i] = v_[n*m_ + i];
  }
  return Vector<T>(result);
}

template<typename T>
Vector<T> DenseMatrix<T>::col(const size_t n) const {
  std::vector<T> result(n_);
  for(size_t i = 0; i < n_; i++) {
    result[i] = v_[i*m_ + n];
  }
  return Vector<T>(result);
}

template<typename T>
void DenseMatrix<T>::swap_row(const size_t row1, const size_t row2) {
  for(size_t j = 0; j < m_; j++) {
    std::swap(v_[row1*m_ + j], v_[row2*m_ + j]);
  }
}

template<typename T>
void DenseMatrix<T>::swap_col(const size_t col1, const size_t col2) {
  for(size_t i = 0; i < n_; i++) {
    std::swap(v_[i*m_ + col1], v_[i*m_ + col2]);
  }
}

template<typename T>
inline T &DenseMatrix<T>::operator[](const size_t pos) {
  return v_[pos];
}

template<typename T>
inline const T &DenseMatrix<T>::operator[](const size_t pos) const {
  return v_[pos];
}

template<typename T>
inline T &DenseMatrix<T>::operator()(const size_t row,
                                     const size_t col) {
  return v_[row*m_ + col];
}

template<typename T>
inline const T &DenseMatrix<T>::operator()(const size_t row,
                                           const size_t col) const {
  return v_[row*m_ + col];
}

// ----------------------------------------------------------------------
// DenseMatrix Inverse
//
template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::inverse() {
  apply_inverse(*this);

  return *this;
}

// ----------------------------------------------------------------------
// DenseMatrix Transpose
//
template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::transpose() {
  apply_transpose(*this);

  return *this;
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_DENSE_DENSE_HPP
