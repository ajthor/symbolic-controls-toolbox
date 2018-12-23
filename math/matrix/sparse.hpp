#ifndef MATH_MATRIX_SPARSE_HPP
#define MATH_MATRIX_SPARSE_HPP

#include "matrix.hpp"

namespace Controls {
namespace Math {

// Direct Methods for Sparse Linear Systems Timothy Davis

// ----------------------------------------------------------------------
// BaseSparseMatrix
//
template<typename T, typename Derived>
class BaseSparseMatrix : public BaseMatrix<T, Derived> {
protected:
  size_t nrows_;
  size_t ncols_;

  std::vector<size_t> i_;
  std::vector<size_t> j_;
  std::vector<T> v_;

public:
  BaseSparseMatrix(const size_t nrows,
             const size_t ncols) :
             nrows_(nrows),
             ncols_(ncols) {
    v_ = std::vector<T>(nrows*ncols);
  }

  BaseSparseMatrix(const size_t nrows,
             const size_t ncols,
             const std::vector<T> v) :
             nrows_(nrows),
             ncols_(ncols),
             v_(v) {}

  inline size_t size();
  inline size_t capacity();

  inline bool empty();

  inline typename std::vector<T>::iterator begin();
  inline typename std::vector<T>::iterator end();
  inline typename std::vector<T>::const_iterator begin() const;
  inline typename std::vector<T>::const_iterator end() const;
  inline typename std::vector<T>::const_iterator cbegin() const;
  inline typename std::vector<T>::const_iterator cend() const;

  inline size_t nrows();
  inline size_t ncols();

  inline std::vector<T> as_vec();

  std::vector<T> row(const size_t n);
  std::vector<T> col(const size_t n);

  inline T &operator[](const size_t pos);
  inline const T &operator[](const size_t pos) const;
  inline T &operator()(const size_t row, const size_t col);
  inline const T &operator()(const size_t row, const size_t col) const;

  // void reshape(const size_t row, const size_t col);

  // void transpose();
};

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_SPARSE_HPP */