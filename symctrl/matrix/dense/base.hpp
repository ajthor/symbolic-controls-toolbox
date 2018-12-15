#ifndef SYMCTRL_MATRIX_DENSE_BASE_HPP
#define SYMCTRL_MATRIX_DENSE_BASE_HPP

#include <vector>

namespace Controls {

// ----------------------------------------------------------------------
// Dense Matrix Base
//
template<typename Derived>
class DenseMatrixBase : public MatrixBase<Derived> {
public:
  ~DenseMatrixBase() {}
};

template<typename T>
class DenseMatrix : DenseMatrixBase<DenseMatrix<T>> {
protected:
  // typedef elem_type T;

  std::vector<T> v_;

  size_t nrows_;
  size_t ncols_;

public:
  typedef typename std::vector<T>::iterator iterator;

  DenseMatrix(size_t rows = 1,
              size_t cols = 1) :
              nrows_(rows),
              ncols_(cols) {
    v_.reserve(rows*cols);
  }
  DenseMatrix(size_t rows,
              size_t cols,
              std::vector<T> values) :
              nrows_(rows),
              ncols_(cols),
              v_(values) {}
  ~DenseMatrix() {}

  iterator begin() { return v_.begin(); }
  iterator end() { return v_.end(); }

  size_t nrows() const { return nrows_; }
  size_t ncols() const { return ncols_; }

  T &operator()(const size_t row, const size_t col) {
    // matrix[ i ][ j ] = array[ i*m + j ]
    return v_[row*ncols_ + col];
  }
  const T &operator()(const size_t row, const size_t col) const {
    // matrix[ i ][ j ] = array[ i*m + j ]
    return v_[row*ncols_ + col];
  }

  std::vector<T> as_vec() { return v_; }
};

template<typename T>
void ones(DenseMatrix<T> &M) {
  size_t i, j;
  for(i = 0; i < M.nrows(); i++) {
    for(j = 0; j < M.ncols(); j++) {
      M(i, j) = 1;
    }
  }
  // for(auto it = M.begin(); it != M.end(); ++it) {
  //   *it = 1;
  // }
}

template<typename T>
void zeros(DenseMatrix<T> &M) {
  size_t i, j;
  for(i = 0; i < M.nrows(); i++) {
    for(j = 0; j < M.ncols(); j++) {
      M(i, j) = 0;
    }
  }
  // for(auto it = M.begin(); it != M.end(); ++it) {
  //   *it = 0;
  // }
}

template<typename T>
void eye(DenseMatrix<T> &M) {
  size_t i, j;
  for(i = 0; i < M.nrows(); i++) {
    for(j = 0; j < M.ncols(); j++) {
      M(i, j) = (i == j) ? 1 : 0;
    }
  }
}
// void diag(DenseMatrix &M, std::vector<T> &v, int k);

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_DENSE_BASE_HPP */
