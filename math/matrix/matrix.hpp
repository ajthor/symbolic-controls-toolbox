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
template<typename T, typename Derived>
class Matrix {
public:
  inline Derived &operator~() {
    return *static_cast<Derived *>(this);
  }
  inline const Derived &operator~() const {
    return *static_cast<const Derived *>(this);
  }

  inline T &operator[](const size_t pos);
  inline const T &operator[](const size_t pos) const;
};

// ----------------------------------------------------------------------
// Matrix Derived Functions
//
template<typename T, typename Derived>
size_t size(Matrix<T, Derived> &m) {
  return (~m).size();
}

template<typename T, typename Derived>
size_t capacity(Matrix<T, Derived> &m) {
  return (~m).capacity();
}

template<typename T, typename Derived>
bool empty(Matrix<T, Derived> &m) {
  return (~m).empty();
}

template<typename T, typename Derived>
typename std::vector<T>::iterator
begin(Matrix<T, Derived> &m) {
  return (~m).begin();
}

template<typename T, typename Derived>
typename std::vector<T>::iterator
end(Matrix<T, Derived> &m) {
  return (~m).end();
}

template<typename T, typename Derived>
typename std::vector<T>::const_iterator
begin(const Matrix<T, Derived> &m) {
  return (~m).begin();
}

template<typename T, typename Derived>
typename std::vector<T>::const_iterator
end(const Matrix<T, Derived> &m) {
  return (~m).end();
}

template<typename T, typename Derived>
typename std::vector<T>::const_iterator
cbegin(const Matrix<T, Derived> &m) {
  return (~m).cbegin();
}

template<typename T, typename Derived>
typename std::vector<T>::const_iterator
cend(const Matrix<T, Derived> &m) {
  return (~m).cend();
}

template<typename T, typename Derived>
size_t nrows(Matrix<T, Derived> &m) {
  return (~m).nrows();
}

template<typename T, typename Derived>
size_t ncols(Matrix<T, Derived> &m) {
  return (~m).ncols();
}

template<typename T, typename Derived>
std::vector<T> as_vec(Matrix<T, Derived> &m) {
  return (~m).as_vec();
}

template<typename T, typename Derived>
inline T &Matrix<T, Derived>::operator[](const size_t pos) {
  return (this)->operator[](pos);
}

template<typename T, typename Derived>
inline const T &Matrix<T, Derived>::operator[](const size_t pos) const {
  return (this)->operator[](pos);
}

template<typename T, typename Derived>
void reshape(Matrix<T, Derived> &m, const size_t row, const size_t col) {
  (~m).reshape(row, col);
}

template<typename T, typename Derived>
inline void transpose(Matrix<T, Derived> &m) {
  (~m).transpose();
}

// ----------------------------------------------------------------------
// Matrix Assignment Functions
//
template<typename T1, typename D1, typename T2, typename D2>
inline void apply_(Matrix<T1, D1> &lhs, const Matrix<T2, D2> &rhs) {
  (~lhs).apply(~rhs);
}

template<typename T1, typename D1, typename T2, typename D2>
inline void apply_add_(Matrix<T1, D1> &lhs, const Matrix<T2, D2> &rhs) {
  (~lhs).apply_add(~rhs);
}

template<typename T1, typename D1, typename T2, typename D2>
inline void apply_mul_(Matrix<T1, D1> &lhs, const Matrix<T2, D2> &rhs) {
  (~lhs).apply_mul(~rhs);
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_MATRIX_HPP */
