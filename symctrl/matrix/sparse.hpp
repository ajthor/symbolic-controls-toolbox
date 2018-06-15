#ifndef SYMCTRL_MATRIX_SPARSE_HPP
#define SYMCTRL_MATRIX_SPARSE_HPP

#include <tuple>

namespace Controls {

// ----------------------------------------------------------------------
// Sparse Matrix (DOK)
//
// Sparse matrix implementation using DOK (dictionary of keys) format.
//
// This class is used to construct a sparse matrix, but is not as efficient as
// the CSR matrix for operations. Large sparse matrices should be converted to
// CSR format before performing operations on them.
template<typename T>
class DOKMatrix {
private:
  size_t row_;
  size_t col_;

  std::map<std::tuple<size_t, size_t>, T> d_;

public:
  DOKMatrix();
  DOKMatrix(const size_t row, const size_t col);
  DOKMatrix(const size_t row, const size_t col,
            std::vector<size_t> i, std::vector<size_t> j,
            std::vector<T> v);

  DOKMatrix(CSRMatrix &m);

  ~DOKMatrix() {}

  size_t nrows() const;
  size_t ncols() const;

  T get(size_t i, size_t j) const;
  void set(size_t i, size_t j, T v) const;

  void add_scalar(T &c, DOKMatrix &result) const;
  void add_matrix(DOKMatrix<T> &m, DOKMatrix<T> &result) const;

  void mul_scalar(T &c, DOKMatrix &result) const;
  void mul_vector(std::vector<T> &v, DOKMatrix<T> &result) const;
  void mul_matrix(DOKMatrix<T> &m, DOKMatrix<T> &result) const;
};

template<typename T>
T DOKMatrix::get(size_t i, size_t j) const {
  return d_[std::make_tuple(i, j)];
}

template<typename T>
void DOKMatrix::set(size_t i, size_t j, T v) const {
  d_[std::make_tuple(i, j)] = v;
}

// ----------------------------------------------------------------------
// Sparse Matrix (CSR)
//
// Sparse matrix implementation using CSR format.
//
// This class is used to operate on a sparse matrix. It is not efficient to
// construct a CSR matrix incrementally, and more efficient to create a sparse
// matrix using the DOK format and then convert to CSR once all values are set.
template<typename T>
class CSRMatrix {
private:
  size_t row_;
  size_t col_;

  std::vector<T> i_;
  std::vector<T> j_;
  std::vector<T> v_;

public:
  CSRMatrix();
  CSRMatrix(const size_t row, const size_t col);
  CSRMatrix(const size_t row, const size_t col,
            std::vector<size_t> i, std::vector<size_t> j,
            std::vector<T> v);

  CSRMatrix(DOKMatrix &m);

  ~CSRMatrix() {}

  size_t nrows() const;
  size_t ncols() const;

  void add_scalar(T &c, CSRMatrix &result) const;
  void add_matrix(CSRMatrix<T> &m, CSRMatrix<T> &result) const;

  void mul_scalar(T &c, CSRMatrix &result) const;
  void mul_vector(std::vector<T> &v, CSRMatrix<T> &result) const;
  void mul_matrix(CSRMatrix<T> &m, CSRMatrix<T> &result) const;
};

CSRMatrix::CSRMatrix() {
  row_ = 0;
  col_ = 0;
}

CSRMatrix::CSRMatrix(const size_t row, const size_t col) {
  row_ = row;
  col_ = col;
}

// Fill a sparse matrix using vectors of indices (i, j) and values.
template<typename T>
CSRMatrix::CSRMatrix(const size_t row, const size_t col,
                     std::vector<size_t> i, std::vector<size_t> j,
                     std::vector<T> v) {
  //
  row_ = row;
  col_ = col;

  size_t k = 0;
  size_t n = i.size();

  // TODO: Ensure indices and values are all the same size.
  if (i.size() != j.size()) {
    // error
  }

  for(k = 0; k < n; k++) {

  }
}

template<typename T>
void add_scalar(T &c, CSRMatrix &result) const {

};

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_SPARSE_HPP */
