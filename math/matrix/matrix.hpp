#ifndef MATH_MATRIX_MATRIX_HPP
#define MATH_MATRIX_MATRIX_HPP

#include <vector>

namespace Controls {
namespace Math {

// // ----------------------------------------------------------------------
// // Matrix
// //
// template<typename T>
// class Matrix {
// public:
//   virtual size_t size() const = 0;
//   virtual size_t capacity() const = 0;
//
//   virtual bool empty() const = 0;
//
//   virtual typename std::vector<T>::iterator begin() = 0;
//   virtual typename std::vector<T>::iterator end() = 0;
//   virtual typename std::vector<T>::const_iterator begin() const = 0;
//   virtual typename std::vector<T>::const_iterator end() const = 0;
//   virtual typename std::vector<T>::const_iterator cbegin() const = 0;
//   virtual typename std::vector<T>::const_iterator cend() const = 0;
//
//   virtual size_t nrows() const = 0;
//   virtual size_t ncols() const = 0;
//
//   virtual std::vector<T> as_vec() const = 0;
//
//   virtual T &operator[](const size_t pos) = 0;
//   virtual const T &operator[](const size_t pos) const = 0;
//
//   virtual void transpose() = 0;
// };

// ----------------------------------------------------------------------
// Matrix
//
template<typename DT>
class Matrix {
public:
  inline DT &operator~() {
    return *static_cast<DT *>(this);
  }
  inline const DT &operator~() const {
    return *static_cast<const DT *>(this);
  }

  // inline T &operator[](const size_t pos);
  // inline const T &operator[](const size_t pos) const;
};

// ----------------------------------------------------------------------
// Matrix DT Functions
//
template<typename DT>
size_t size(Matrix<DT> &m) {
  return (~m).size();
}

template<typename DT>
size_t capacity(Matrix<DT> &m) {
  return (~m).capacity();
}

template<typename DT>
bool empty(Matrix<DT> &m) {
  return (~m).empty();
}

// template<typename DT>
// typename std::vector<T>::iterator
// begin(Matrix<DT> &m) {
//   return (~m).begin();
// }
//
// template<typename DT>
// typename std::vector<T>::iterator
// end(Matrix<DT> &m) {
//   return (~m).end();
// }
//
// template<typename DT>
// typename std::vector<T>::const_iterator
// begin(const Matrix<DT> &m) {
//   return (~m).begin();
// }
//
// template<typename DT>
// typename std::vector<T>::const_iterator
// end(const Matrix<DT> &m) {
//   return (~m).end();
// }
//
// template<typename DT>
// typename std::vector<T>::const_iterator
// cbegin(const Matrix<DT> &m) {
//   return (~m).cbegin();
// }
//
// template<typename DT>
// typename std::vector<T>::const_iterator
// cend(const Matrix<DT> &m) {
//   return (~m).cend();
// }

template<typename DT>
size_t nrows(Matrix<DT> &m) {
  return (~m).nrows();
}

template<typename DT>
size_t ncols(Matrix<DT> &m) {
  return (~m).ncols();
}

// template<typename DT>
// std::vector<T> as_vec(Matrix<DT> &m) {
//   return (~m).as_vec();
// }

// template<typename DT>
// inline T &Matrix<DT>::operator[](const size_t pos) {
//   return (this)->operator[](pos);
// }
//
// template<typename DT>
// inline const T &Matrix<DT>::operator[](const size_t pos) const {
//   return (this)->operator[](pos);
// }

// template<typename DT>
// void reshape(Matrix<DT> &m, const size_t row, const size_t col) {
//   (~m).reshape(row, col);
// }

// template<typename DT>
// inline void transpose(Matrix<DT> &m) {
//   (~m).transpose();
// }

// ----------------------------------------------------------------------
// Matrix Assignment Functions
//
template<typename D1, typename D2>
inline void apply_(Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  (~lhs).apply(~rhs);
}

template<typename D1, typename D2>
inline void apply_add_(Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  (~lhs).apply_add(~rhs);
}

template<typename D1, typename D2>
inline void apply_mul_(Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  (~lhs).apply_mul(~rhs);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_MATRIX_HPP */
