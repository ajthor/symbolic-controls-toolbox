#ifndef MATH_MATRIX_VECTOR_HPP
#define MATH_MATRIX_VECTOR_HPP

#include <algorithm>

#include "assert.hpp"
#include "matrix.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Vector
//
template<typename T>
class Vector : public Matrix<Vector<T>> {
private:
  size_t n_;
  size_t m_;

  std::vector<T> v_;

public:
  explicit inline Vector();

  explicit inline Vector(const size_t count);

  explicit inline Vector(const std::vector<T> v);

  inline Vector(const Vector<T> &m);

  inline Vector<T> &operator=(const T &rhs);
  inline Vector<T> &operator=(const std::vector<T> rhs);
  inline Vector<T> &operator=(const Vector<T> &rhs);

  template<typename DT>
  inline Vector<T> &operator=(const Matrix<DT> &rhs);

  inline Vector<T> &operator+=(const T &rhs);
  inline Vector<T> &operator-=(const T &rhs);
  inline Vector<T> &operator*=(const T &rhs);
  inline Vector<T> &operator/=(const T &rhs);

  template<typename DT>
  inline void apply(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_add(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_mul(const Matrix<DT> &rhs);
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

  inline T &operator[](const size_t pos);
  inline const T &operator[](const size_t pos) const;

  inline T &operator()(const size_t pos);
  inline const T &operator()(const size_t pos) const;

  // void reshape(const size_t row, const size_t col);

  inline Vector<T> &transpose();
};

// ----------------------------------------------------------------------
// Vector Constructor
//
template<typename T>
inline Vector<T>::Vector() :
                         n_(0),
                         m_(0) {
  v_ = std::vector<T>(0);
}

template<typename T>
inline Vector<T>::Vector(const size_t count) :
                         n_(count),
                         m_(1) {
  v_ = std::vector<T>(count);
}

template<typename T>
inline Vector<T>::Vector(const std::vector<T> v) :
                         n_(v.size()),
                         m_(1),
                         v_(v) {
  //
}

template<typename T>
inline Vector<T>::Vector(const Vector<T> &m) :
                         n_(m.n_),
                         m_(m.m_),
                         v_(m.v_) {
  //
}

// ----------------------------------------------------------------------
// Vector Assignment Operator
//
template<typename T>
inline Vector<T> &Vector<T>::operator=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = rhs;
  }

  return *this;
}

template<typename T>
inline Vector<T> &Vector<T>::operator=(const std::vector<T> rhs) {
  n_ = rhs.size();
  m_ = 1;
  v_ = rhs;

  return *this;
}

template<typename T>
inline Vector<T> &Vector<T>::operator=(const Vector<T> &rhs) {
  n_ = rhs.n_;
  m_ = rhs.m_;
  v_ = rhs.v_;

  return *this;
}

template<typename T>
template<typename DT>
inline Vector<T> &Vector<T>::operator=(const Matrix<DT> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

template<typename T>
inline Vector<T> &Vector<T>::operator+=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] += rhs;
  }

  return *this;
}

template<typename T>
inline Vector<T> &Vector<T>::operator-=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] -= rhs;
  }

  return *this;
}

template<typename T>
inline Vector<T> &Vector<T>::operator*=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] *= rhs;
  }

  return *this;
}

template<typename T>
inline Vector<T> &Vector<T>::operator/=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] /= rhs;
  }

  return *this;
}

template<typename T>
template<typename DT>
inline void Vector<T>::apply(const Matrix<DT> &rhs) {
  n_ = (~rhs).n_;
  m_ = (~rhs).m_;
  v_ = (~rhs).v_;
}

template<typename T>
template<typename DT>
inline void Vector<T>::apply_add(const Matrix<DT> &rhs) {
  MATRIX_ASSERT(n_ == (~rhs).n_);
  MATRIX_ASSERT(m_ == (~rhs).m_);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      v_[i*m_ + j] += (~rhs)[i*m_ + j];
    }
  }
}

template<typename T>
template<typename DT>
inline void Vector<T>::apply_mul(const Matrix<DT> &rhs) {
  MATRIX_ASSERT(m_ == (~rhs).n_);

  std::vector<T> t_(n_*(~rhs).m_, 0);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < (~rhs).m_; j++) {

      for(size_t k = 0; k < m_; k++) {
        t_[i*(~rhs).m_ + j] += v_[i*m_ + k] * (~rhs)[k*(~rhs).m_ + j];
      }
    }
  }

  m_ = (~rhs).m_;
  v_ = t_;
}

template<typename T>
template<typename DT>
inline void Vector<T>::apply_transpose(const Matrix<DT> &rhs) {
  size_t tmp = (~rhs).n_;
  n_ = (~rhs).m_;
  m_ = tmp;
  v_ = (~rhs).v_;
}

// ----------------------------------------------------------------------
// Vector Member Function Definitions
//
template<typename T>
inline size_t Vector<T>::size() const {
  return v_.size();
}

template<typename T>
inline size_t Vector<T>::capacity() const {
  return v_.capacity();
}

template<typename T>
inline bool Vector<T>::empty() const {
  return v_.empty();
}

template<typename T>
inline typename std::vector<T>::iterator
Vector<T>::begin() {
  return v_.begin();
}

template<typename T>
inline typename std::vector<T>::iterator
Vector<T>::end() {
  return v_.begin();
}

template<typename T>
inline typename std::vector<T>::const_iterator
Vector<T>::begin() const {
  return v_.begin();
}

template<typename T>
inline typename std::vector<T>::const_iterator
Vector<T>::end() const {
  return v_.begin();
}

template<typename T>
inline typename std::vector<T>::const_iterator
Vector<T>::cbegin() const {
  return v_.begin();
}

template<typename T>
inline typename std::vector<T>::const_iterator
Vector<T>::cend() const {
  return v_.begin();
}

template<typename T>
inline size_t Vector<T>::nrows() const {
  return n_;
}

template<typename T>
inline size_t Vector<T>::ncols() const {
  return m_;
}

template<typename T>
inline std::vector<T> Vector<T>::as_vec() const {
  return v_;
}

template<typename T>
inline T &Vector<T>::operator[](const size_t pos) {
  return v_[pos];
}

template<typename T>
inline const T &Vector<T>::operator[](const size_t pos) const {
  return v_[pos];
}

template<typename T>
inline T &Vector<T>::operator()(const size_t pos) {
  return v_[pos];
}

template<typename T>
inline const T &Vector<T>::operator()(const size_t pos) const {
  return v_[pos];
}

// template<typename T>
// void Vector<T>::reshape(const size_t row, const size_t col) {
//
// }

// ----------------------------------------------------------------------
// Vector Transpose
//
template<typename T>
inline Vector<T> &Vector<T>::transpose() {
  apply_transpose(*this);

  return *this;
}

// ----------------------------------------------------------------------
// Vector Helper Functions
//
template<typename T>
void ones(Vector<T> &M) {
  size_t i, j;
  for(i = 0; i < M.nrows(); i++) {
    for(j = 0; j < M.ncols(); j++) {
      M(i, j) = 1;
    }
  }
}

template<typename T>
void zeros(Vector<T> &M) {
  size_t i, j;
  for(i = 0; i < M.nrows(); i++) {
    for(j = 0; j < M.ncols(); j++) {
      M(i, j) = 0;
    }
  }
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_VECTOR_HPP */