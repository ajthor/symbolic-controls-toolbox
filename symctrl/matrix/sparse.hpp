#ifndef SYMCTRL_MATRIX_SPARSE_HPP
#define SYMCTRL_MATRIX_SPARSE_HPP

#include <tuple>

namespace Controls {

// ----------------------------------------------------------------------
// Sparse Matrix Base
//
template<typename T>
class SparseMatrixBase {
private:
  size_t row_;
  size_t col_;

public:
  virtual ~SparseMatrixBase();

  size_t nrows() const;
  size_t ncols() const;

  virtual T get(size_t i, size_t j) const;
  virtual T get(std::tuple<size_t, size_t> t) const;
  virtual void set(size_t i, size_t j, T v) const;
  virtual void set(std::tuple<size_t, size_t> t, T v) const;
};

// Forward declarations.
template<typename T> class CSRMatrix;
template<typename T> class DOKMatrix;
template<typename T> class COOMatrix;

// ----------------------------------------------------------------------
// Sparse Matrix (COO)
//
// class COOMatrix : public SparseMatrixBase {
//
// };

// ----------------------------------------------------------------------
// Sparse Matrix (DOK)
//
// Sparse matrix implementation using DOK (dictionary of keys) format.
//
// This class is used to construct a sparse matrix, but is not as efficient as
// the CSR matrix for operations. Large sparse matrices should be converted to
// CSR format before performing operations on them.
template<typename T>
class DOKMatrix : public SparseMatrixBase<T> {
private:
  std::map<std::tuple<size_t, size_t>, T> d_;

public:
  DOKMatrix();
  DOKMatrix(const size_t row, const size_t col);
  DOKMatrix(const size_t row, const size_t col,
            std::vector<size_t> i, std::vector<size_t> j,
            std::vector<T> v);

  DOKMatrix(CSRMatrix<T> &m);

  ~DOKMatrix() {}

  virtual T get(size_t i, size_t j) const;
  virtual T get(std::tuple<size_t, size_t> t) const;
  virtual void set(size_t i, size_t j, T v) const;
  virtual void set(std::tuple<size_t, size_t> t, T v) const;

  void add_scalar(T &c, DOKMatrix<T> &result) const;
  void add_matrix(DOKMatrix<T> &m, DOKMatrix<T> &result) const;

  void mul_scalar(T &c, DOKMatrix<T> &result) const;
  void mul_vector(std::vector<T> &v, DOKMatrix<T> &result) const;
  void mul_matrix(DOKMatrix<T> &m, DOKMatrix<T> &result) const;
};

template<typename T>
T DOKMatrix<T>::get(size_t i, size_t j) const {
  DOKMatrix<T>::get(std::make_tuple(i, j));
}

template<typename T>
T DOKMatrix<T>::get(std::tuple<size_t, size_t> t) const {
  return d_[t];
}

template<typename T>
void DOKMatrix<T>::set(size_t i, size_t j, T v) const {
  DOKMatrix<T>::set(std::make_tuple(i, j), v);
}

template<typename T>
void DOKMatrix<T>::set(std::tuple<size_t, size_t> t, T v) const {
  d_[t] = v;
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
class CSRMatrix : public SparseMatrixBase<T> {
private:
  std::vector<T> i_;
  std::vector<T> j_;
  std::vector<T> v_;

public:
  CSRMatrix();
  CSRMatrix(const size_t row, const size_t col);
  CSRMatrix(const size_t row, const size_t col,
            std::vector<size_t> i, std::vector<size_t> j,
            std::vector<T> v);

  CSRMatrix(DOKMatrix<T> &m);

  ~CSRMatrix() {}

  void add_scalar(T &c, CSRMatrix<T> &result) const;
  void add_matrix(CSRMatrix<T> &m, CSRMatrix<T> &result) const;

  void mul_scalar(T &c, CSRMatrix<T> &result) const;
  void mul_vector(std::vector<T> &v, CSRMatrix<T> &result) const;
  void mul_matrix(CSRMatrix<T> &m, CSRMatrix<T> &result) const;
};

template<typename T>
CSRMatrix<T>::CSRMatrix() {
  this->row_ = 0;
  this->col_ = 0;
}

template<typename T>
CSRMatrix<T>::CSRMatrix(const size_t row, const size_t col) {
  this->row_ = row;
  this->col_ = col;
}

// Fill a sparse matrix using vectors of indices (i, j) and values.
template<typename T>
CSRMatrix<T>::CSRMatrix(const size_t row, const size_t col,
                     std::vector<size_t> i, std::vector<size_t> j,
                     std::vector<T> v) {
  //
  this->row_ = row;
  this->col_ = col;

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
void CSRMatrix<T>::add_scalar(T &c, CSRMatrix<T> &result) const {

};

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_SPARSE_HPP */
