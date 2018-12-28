#ifndef MATH_MATRIX_DENSE_HPP
#define MATH_MATRIX_DENSE_HPP

#include <algorithm>
#include <type_traits>

#include "assert.hpp"
#include "matrix.hpp"

#include <math/traits/is_symbolic.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// DenseMatrix
//
template<typename T>
class DenseMatrix : public Matrix<DenseMatrix<T>> {
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

  template<typename DT>
  inline auto apply_jacobian(const Matrix<DT> &f, const Matrix<DT> &v)
  -> enable_if_symbolic_t<DT>;

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

  std::vector<T> row(const size_t n) const;
  std::vector<T> col(const size_t n) const;

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
  v_ = std::vector<T>(nrows*ncols);
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

template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator+=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] += rhs;
  }

  return *this;
}

template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator-=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] -= rhs;
  }

  return *this;
}

template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator*=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] *= rhs;
  }

  return *this;
}

template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator/=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] /= rhs;
  }

  return *this;
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply(const Matrix<DT> &rhs) {
  n_ = (~rhs).nrows();
  m_ = (~rhs).ncols();
  v_ = (~rhs).as_vec();
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_add(const Matrix<DT> &rhs) {
  MATRIX_ASSERT(n_ == (~rhs).nrows());
  MATRIX_ASSERT(m_ == (~rhs).ncols());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      v_[i*m_ + j] += (~rhs)[i*m_ + j];
    }
  }
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_sub(const Matrix<DT> &rhs) {
  MATRIX_ASSERT(n_ == (~rhs).nrows());
  MATRIX_ASSERT(m_ == (~rhs).ncols());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      v_[i*m_ + j] -= (~rhs)[i*m_ + j];
    }
  }
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_mul(const Matrix<DT> &rhs) {
  MATRIX_ASSERT(m_ == (~rhs).nrows());

  std::vector<T> t_(n_*(~rhs).ncols(), 0);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {

      for(size_t k = 0; k < m_; k++) {
        t_[i*(~rhs).ncols() + j] += v_[i*m_ + k] * (~rhs)[k*(~rhs).ncols() + j];
      }
    }
  }

  m_ = (~rhs).ncols();
  v_ = t_;
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_inverse(const Matrix<DT> &rhs) {
  MATRIX_ASSERT(v_.size() == (~rhs).size());

  std::vector<T> t_((~rhs).size());

  for(size_t i = 0; i < (~rhs).nrows(); i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {
      t_[j*(~rhs).nrows() + i] = (~rhs)[i*(~rhs).ncols() + j];
    }
  }

  size_t tmp = (~rhs).nrows();
  n_ = (~rhs).ncols();
  m_ = tmp;
  v_ = t_;
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_transpose(const Matrix<DT> &rhs) {
  MATRIX_ASSERT(v_.size() == (~rhs).size());

  std::vector<T> t_((~rhs).size());

  for(size_t i = 0; i < (~rhs).nrows(); i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {
      t_[j*(~rhs).nrows() + i] = (~rhs)[i*(~rhs).ncols() + j];
    }
  }

  size_t tmp = (~rhs).nrows();
  n_ = (~rhs).ncols();
  m_ = tmp;
  v_ = t_;
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
      if(!equal((~lhs)(i, j), (~rhs)(i, j)))
        return false;
    }
  }

  return true;
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
  return v_.begin();
}

template<typename T>
inline typename std::vector<T>::const_iterator
DenseMatrix<T>::begin() const {
  return v_.begin();
}

template<typename T>
inline typename std::vector<T>::const_iterator
DenseMatrix<T>::end() const {
  return v_.begin();
}

template<typename T>
inline typename std::vector<T>::const_iterator
DenseMatrix<T>::cbegin() const {
  return v_.begin();
}

template<typename T>
inline typename std::vector<T>::const_iterator
DenseMatrix<T>::cend() const {
  return v_.begin();
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
std::vector<T> DenseMatrix<T>::row(const size_t n) const {
  std::vector<T> result(m_);
  for(size_t i = 0; i < m_; i++) {
    result[i] = v_[n*m_ + i];
  }
  return result;
}

template<typename T>
std::vector<T> DenseMatrix<T>::col(const size_t n) const {
  std::vector<T> result(n_);
  for(size_t i = 0; i < n_; i++) {
    result[i] = v_[i*m_ + n];
  }
  return result;
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

// // ----------------------------------------------------------------------
// // DenseMatrix Helper Functions
// //
// template<typename T>
// DenseMatrix<T> &ones(const size_t nrows, const size_t ncols) {
//   DenseMatrix<T> M(nrows, ncols);
//   size_t i, j;
//   for(i = 0; i < nrows; i++) {
//     for(j = 0; j < ncols; j++) {
//       M(i, j) = 1;
//     }
//   }
//   return &M;
// }
//
// template<typename T>
// DenseMatrix<T> &ones(const size_t size) {
//   return ones(size, size);
// }
//
// template<typename T>
// DenseMatrix<T> &zeros(const size_t nrows, const size_t ncols) {
//   DenseMatrix<T> M(nrows, ncols);
//   size_t i, j;
//   for(i = 0; i < nrows; i++) {
//     for(j = 0; j < ncols; j++) {
//       M(i, j) = 0;
//     }
//   }
//   return &M;
// }
//
// template<typename T>
// DenseMatrix<T> &zeros(const size_t size) {
//   return zeros(size, size);
// }
//
// template<typename T>
// DenseMatrix<T> &eye(const size_t nrows, const size_t ncols) {
//   DenseMatrix<T> M(nrows, ncols);
//   size_t i, j;
//   for(i = 0; i < nrows; i++) {
//     for(j = 0; j < ncols; j++) {
//       M(i, j) = (i == j) ? 1 : 0;
//     }
//   }
//   return &M;
// }
//
// template<typename T>
// DenseMatrix<T> &eye(const size_t size) {
//   return eye(size, size);
// }
// // void diag(DenseMatrix &M, std::vector<T> &v, int k);

// ----------------------------------------------------------------------
// DenseMatrix Structure Functions
//
template<typename T>
bool is_symmetric(const DenseMatrix<T> &m) {
  size_t i, j;
  for(i = 1; i < m.nrows(); ++i) {
    for(j = 0; j < i; ++j) {
      if(!equal(m(i, j), m(j, i))) {
        return false;
      }
    }
  }

  return true;
}

template<typename T>
bool is_upper(const DenseMatrix<T> &m) {
  size_t i, j;
  for(i = 1; i < m.nrows(); ++i) {
    for(j = 0; j < i; ++j) {
      if(!is_default(m(i, j))) {
        return false;
      }
    }
  }

  return true;
}

template<typename T>
bool is_lower(const DenseMatrix<T> &m) {
  size_t i, j;
  for(i = 1; i < m.ncols(); ++i) {
    for(j = 0; j < i; ++j) {
      if(!is_default(m(j, i))) {
        return false;
      }
    }
  }

  return true;
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_DENSE_HPP */
