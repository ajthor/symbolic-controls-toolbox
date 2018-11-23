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
private:
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
  std::vector<T> row(size_t n) {

  }
  std::vector<T> col(size_t n) {

  }
};

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_DENSE_BASE_HPP */
