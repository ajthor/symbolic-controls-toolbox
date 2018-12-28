#ifndef MATH_MATRIX_BLOCK_HPP
#define MATH_MATRIX_BLOCK_HPP

#include <algorithm>

#include "assert.hpp"
#include "matrix.hpp"
#include "dense.hpp"

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// BlockMatrix
//
template<typename T>
class BlockMatrix : public Matrix<BlockMatrix<T>> {
private:
  using MT = DenseMatrix<T>;

  size_t n_;
  size_t m_;

  std::vector<MT> v_;

public:
  explicit inline BlockMatrix();
  explicit inline BlockMatrix(const size_t nrows,
                              const size_t ncols);
  explicit inline BlockMatrix(const size_t nrows,
                              const size_t ncols,
                              const std::vector<MT> v);

  inline BlockMatrix(const BlockMatrix<T> &m);

  inline BlockMatrix<T> &operator=(const T &rhs);
  inline BlockMatrix<T> &operator=(const MT &rhs);
  inline BlockMatrix<T> &operator=(const BlockMatrix<T> &rhs);

  template<typename DT>
  inline BlockMatrix<T> &operator=(const Matrix<DT> &rhs);

  inline BlockMatrix<T> &operator+=(const T &rhs);
  inline BlockMatrix<T> &operator-=(const T &rhs);
  inline BlockMatrix<T> &operator*=(const T &rhs);
  inline BlockMatrix<T> &operator/=(const T &rhs);

  template<typename DT>
  inline void apply(const BlockMatrix<DT> &rhs);
  template<typename DT>
  inline void apply_add(const BlockMatrix<DT> &rhs);
  template<typename DT>
  inline void apply_sub(const BlockMatrix<DT> &rhs);
  template<typename DT>
  inline void apply_mul(const BlockMatrix<DT> &rhs);
  template<typename DT>
  inline void apply_inverse(const BlockMatrix<DT> &rhs);
  template<typename DT>
  inline void apply_transpose(const BlockMatrix<DT> &rhs);

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline std::vector<MT> as_vec() const;
  inline DenseMatrix<T> as_dense() const;

  inline MT *operator[](const size_t pos);
  inline const MT *operator[](const size_t pos) const;

  inline MT *operator()(const size_t row, const size_t col);
  inline const MT *operator()(const size_t row, const size_t col) const;
};

// ----------------------------------------------------------------------
// BlockMatrix Constructor
//
template<typename T>
inline BlockMatrix<T>::BlockMatrix() :
                                   n_(0),
                                   m_(0) {
  //
  v_ = std::vector<MT>(0);
}

template<typename T>
inline BlockMatrix<T>::BlockMatrix(const size_t nrows,
                                   const size_t ncols) :
                                   n_(nrows),
                                   m_(ncols) {
  //
  v_ = std::vector<MT>(nrows*ncols);
}

template<typename T>
inline BlockMatrix<T>::BlockMatrix(const size_t nrows,
                                   const size_t ncols,
                                   const std::vector<MT> v) :
                                   n_(nrows),
                                   m_(ncols),
                                   v_(v) {
  //  
  size_t row_size, col_size;

  // Assert row sizes are consistent.
  for(size_t i = 0; i < n_; i++) {
    row_size = v_[i*m_].nrows();

    for(size_t j = 0; j < m_; j++) {
      MATRIX_ASSERT(v_[i*m_ + j].nrows() == row_size);
    }
  }

  // Assert column sizes are consistent.
  for(size_t j = 0; j < m_; j++) {
    col_size = v_[j].ncols();

    for(size_t i = 0; i < n_; i++) {
      MATRIX_ASSERT(v_[i*m_ + j].ncols() == col_size);
    }
  }
}

template<typename T>
inline BlockMatrix<T>::BlockMatrix(const BlockMatrix<T> &m) :
                                   n_(m.n_),
                                   m_(m.m_),
                                   v_(m.v_) {
  //
}

// ----------------------------------------------------------------------
// BlockMatrix Assignment Operator
//
template<typename T>
inline BlockMatrix<T> &BlockMatrix<T>::operator=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = rhs;
  }

  return *this;
}

template<typename T>
inline BlockMatrix<T> &BlockMatrix<T>::operator=(const MT &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = rhs;
  }

  return *this;
}

template<typename T>
inline BlockMatrix<T> &BlockMatrix<T>::operator=(const BlockMatrix<T> &rhs) {
  n_ = rhs.n_;
  m_ = rhs.m_;
  v_ = rhs.v_;

  return *this;
}

template<typename T>
template<typename DT>
inline BlockMatrix<T> &BlockMatrix<T>::operator=(const Matrix<DT> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

template<typename T>
inline BlockMatrix<T> &BlockMatrix<T>::operator+=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] += rhs;
  }

  return *this;
}

template<typename T>
inline BlockMatrix<T> &BlockMatrix<T>::operator-=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] -= rhs;
  }

  return *this;
}

template<typename T>
inline BlockMatrix<T> &BlockMatrix<T>::operator*=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] *= rhs;
  }

  return *this;
}

template<typename T>
inline BlockMatrix<T> &BlockMatrix<T>::operator/=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] /= rhs;
  }

  return *this;
}

template<typename T>
template<typename DT>
inline void BlockMatrix<T>::apply(const BlockMatrix<DT> &rhs) {
  n_ = (~rhs).nrows();
  m_ = (~rhs).ncols();
  v_ = (~rhs).as_vec();
}

template<typename T>
template<typename DT>
inline void BlockMatrix<T>::apply_add(const BlockMatrix<DT> &rhs) {
  MATRIX_ASSERT(n_ == (~rhs).nrows());
  MATRIX_ASSERT(m_ == (~rhs).ncols());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      MATRIX_ASSERT(v_[i*m_ + j].nrows() == (~rhs)[i*m_ + j]->nrows());
      MATRIX_ASSERT(v_[i*m_ + j].ncols() == (~rhs)[i*m_ + j]->ncols());

      v_[i*m_ + j].apply_add(*(~rhs)[i*m_ + j]);
    }
  }
}

template<typename T>
template<typename DT>
inline void BlockMatrix<T>::apply_sub(const BlockMatrix<DT> &rhs) {
  MATRIX_ASSERT(n_ == (~rhs).nrows());
  MATRIX_ASSERT(m_ == (~rhs).ncols());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      MATRIX_ASSERT(v_[i*m_ + j].nrows() == (~rhs)[i*m_ + j]->nrows());
      MATRIX_ASSERT(v_[i*m_ + j].ncols() == (~rhs)[i*m_ + j]->ncols());

      v_[i*m_ + j].apply_sub(*(~rhs)[i*m_ + j]);
    }
  }
}

template<typename T>
template<typename DT>
inline void BlockMatrix<T>::apply_mul(const BlockMatrix<DT> &rhs) {
  MATRIX_ASSERT(m_ == (~rhs).nrows());

  std::vector<MT> t_(n_*(~rhs).ncols(), 0);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {

      for(size_t k = 0; k < m_; k++) {
        t_[i*(~rhs).ncols() + j] +=
          v_[i*m_ + k].apply_mul((~rhs)[k*(~rhs).ncols() + j]);
      }
    }
  }

  m_ = (~rhs).ncols();
  v_ = t_;
}

template<typename T>
template<typename DT>
inline void BlockMatrix<T>::apply_inverse(const BlockMatrix<DT> &rhs) {}

template<typename T>
template<typename DT>
inline void BlockMatrix<T>::apply_transpose(const BlockMatrix<DT> &rhs) {
  MATRIX_ASSERT(v_.size() == (~rhs).size());

  std::vector<MT> t_((~rhs).size());

  for(size_t i = 0; i < (~rhs).nrows(); i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {
      t_[j*(~rhs).nrows() + i].apply_transpose((~rhs)[i*(~rhs).ncols() + j]);
    }
  }

  size_t tmp = (~rhs).nrows();
  n_ = (~rhs).ncols();
  m_ = tmp;
  v_ = t_;
}

// ----------------------------------------------------------------------
// BlockMatrix Equal
//
template<typename T>
inline bool equal(const BlockMatrix<T> &lhs, const BlockMatrix<T> &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~lhs).nrows(); i++) {
    for(size_t j = 0; j < (~lhs).ncols(); j++) {
      if(!equal(*(~lhs)(i, j), *(~rhs)(i, j)))
        return false;
    }
  }

  return true;
}

// ----------------------------------------------------------------------
// BlockMatrix Member Function Definitions
//
template<typename T>
inline size_t BlockMatrix<T>::size() const {
  return v_.size();
}
template<typename T>
inline size_t BlockMatrix<T>::capacity() const {
  return v_.capacity();
}

template<typename T>
inline bool BlockMatrix<T>::empty() const {
  return v_.empty();
}

template<typename T>
inline size_t BlockMatrix<T>::nrows() const {
  return n_;
}
template<typename T>
inline size_t BlockMatrix<T>::ncols() const {
  return m_;
}

template<typename T>
inline std::vector<DenseMatrix<T>> BlockMatrix<T>::as_vec() const {
  return v_;
}

template<typename T>
inline DenseMatrix<T> BlockMatrix<T>::as_dense() const {
  size_t nn_, mm_;
  size_t cn_ = 0;
  size_t cm_ = 0;
  size_t tn_ = 0;
  size_t tm_ = 0;
  size_t ts_ = 0;

  for (size_t i = 0; i < n_; i++) {
    tn_ += v_[i*m_].nrows();
  }

  for (size_t j = 0; j < m_; j++) {
    tm_ += v_[j].ncols();
  }

  for (size_t i = 0; i < v_.size(); i++) {
    ts_ += v_[i].size();
  }

  std::vector<T> t_(ts_);

  for(size_t i = 0; i < n_; i++) {
    nn_ = v_[i*m_].nrows();

    for(size_t ii = 0; ii < nn_; ii++) {

      for(size_t j = 0; j < m_; j++) {
        mm_ = v_[i*m_ + j].ncols();

        for(size_t jj = 0; jj < mm_; jj++) {
          t_[(cn_ + ii)*tm_ + cm_ + jj] = v_[i*m_ + j](ii, jj);
        }
        cm_ += mm_;
      }
      cm_ = 0;
    }
    cn_ += nn_;
  }

  return DenseMatrix<T>(tn_, tm_, t_);
}

template<typename T>
inline DenseMatrix<T>*
BlockMatrix<T>::operator[](const size_t pos) {
  return &v_[pos];
}

template<typename T>
inline const DenseMatrix<T>*
BlockMatrix<T>::operator[](const size_t pos) const {
  return &v_[pos];
}

template<typename T>
inline DenseMatrix<T>*
BlockMatrix<T>::operator()(const size_t row, const size_t col) {
  return &v_[row*m_ + col];
}

template<typename T>
inline const DenseMatrix<T>*
BlockMatrix<T>::operator()(const size_t row, const size_t col) const {
  return &v_[row*m_ + col];
}


} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_BLOCK_HPP */
