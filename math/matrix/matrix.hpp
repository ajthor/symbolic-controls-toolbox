#ifndef MATH_MATRIX_MATRIX_HPP
#define MATH_MATRIX_MATRIX_HPP

#include <type_traits>

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

template<typename DT>
size_t nrows(Matrix<DT> &m) {
  return (~m).nrows();
}

template<typename DT>
size_t ncols(Matrix<DT> &m) {
  return (~m).ncols();
}

// ----------------------------------------------------------------------
// Matrix Equal
//
template<typename D1, typename D2>
inline bool is_equal(const Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  return (std::is_same<D1, D2>::value &&
          reinterpret_cast<const void *>(&lhs) ==
          reinterpret_cast<const void *>(&rhs));
}

template<typename D1, typename D2>
inline bool equal(const Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  return is_equal(~lhs, ~rhs);
}

// ----------------------------------------------------------------------
// Value Equal
//
template<typename T>
inline bool equal(const T lhs, const T rhs) {
  return lhs == rhs;
}

template<typename T>
inline bool is_default(const T v) {
  return v == T();
}

// ----------------------------------------------------------------------
// Matrix Equality Operator
//
template<typename D1, typename D2>
inline bool operator==(const Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  return equal(~lhs, ~rhs);
}

template<typename D1, typename D2>
inline bool operator!=(const Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  return !equal(~lhs, ~rhs);
}

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

template<typename D1, typename D2>
inline void apply_inverse_(Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  (~lhs).apply_inverse(~rhs);
}

template<typename D1, typename D2>
inline void apply_transpose_(Matrix<D1> &lhs, const Matrix<D2> &rhs) {
  (~lhs).apply_transpose(~rhs);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_MATRIX_HPP */
