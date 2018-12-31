#ifndef SYMCTRL_MATH_MATRIX_MATRIX_HPP
#define SYMCTRL_MATH_MATRIX_MATRIX_HPP

#include <iomanip>
#include <ostream>
#include <type_traits>
#include <vector>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// BaseMatrix
//
class BaseMatrix {
public:
  virtual ~BaseMatrix() {}
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
};

// ----------------------------------------------------------------------
// Matrix
//
template<typename DT>
class Matrix : public BaseMatrix {
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
// Stream Output
//
// template<template<typename> class DT, typename T>
// inline auto operator<<(std::ostream& os, const Matrix<DT<T>> &m)
// -> typename std::enable_if<std::is_scalar<T>::value, std::ostream&>::type {
//   for(size_t i = 0; i < (~m).nrows(); i++) {
//     os << "| ";
//     for(size_t j = 0; j < (~m).ncols(); j++) {
//       os << std::setw(12) << (~m)[i*(~m).ncols() + j] << " ";
//     }
//     os << "|" << '\n';
//   }
//   return os;
// }


} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_MATRIX_HPP */
