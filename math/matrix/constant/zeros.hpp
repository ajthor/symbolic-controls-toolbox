#ifndef MATH_MATRIX_CONSTANT_ZEROS_HPP
#define MATH_MATRIX_CONSTANT_ZEROS_HPP

#include <algorithm>

#include <symengine/basic.h>
#include <symengine/constants.h>

#include <math/matrix/dense/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Zeros
//
template<typename T, size_t N, size_t M>
class Zeros : public Matrix<Zeros<T, N, M>> {
private:

public:
  Zeros();

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline std::vector<T> as_vec() const;
  inline DenseMatrix<T> as_dense() const;

  inline T operator[](const size_t pos);
  inline const T operator[](const size_t pos) const;

  inline T operator()(const size_t row, const size_t col);
  inline const T operator()(const size_t row, const size_t col) const;
};

template<typename T, size_t N, size_t M>
Zeros<T, N, M>::Zeros() {
  //
}

template<typename T, size_t N, size_t M>
inline size_t Zeros<T, N, M>::size() const {
  return N*M;
}

template<typename T, size_t N, size_t M>
inline size_t Zeros<T, N, M>::capacity() const {
  return 0;
}

template<typename T, size_t N, size_t M>
inline bool Zeros<T, N, M>::empty() const {
  return false;
}

template<typename T, size_t N, size_t M>
inline size_t Zeros<T, N, M>::nrows() const {
  return N;
}

template<typename T, size_t N, size_t M>
inline size_t Zeros<T, N, M>::ncols() const {
  return M;
}

template<typename T, size_t N, size_t M>
inline std::vector<T> Zeros<T, N, M>::as_vec() const {
  std::vector<T> v_(N*M, T(0));

  return v_;
}

template<typename T, size_t N, size_t M>
inline DenseMatrix<T> Zeros<T, N, M>::as_dense() const {
  std::vector<T> v_ = (*this).as_vec();
  return DenseMatrix<T>(N, M, v_);
}

template<typename T, size_t N, size_t M>
inline T Zeros<T, N, M>::operator[](const size_t pos) {
  return T(0);
}

template<typename T, size_t N, size_t M>
inline const T Zeros<T, N, M>::operator[](const size_t pos) const {
  return T(0);
}

template<typename T, size_t N, size_t M>
inline T Zeros<T, N, M>::operator()(const size_t row,
                                    const size_t col) {
  return T(0);
}

template<typename T, size_t N, size_t M>
inline const T Zeros<T, N, M>::operator()(const size_t row,
                                          const size_t col) const {
  return T(0);
}

// ----------------------------------------------------------------------
// Symbolic Partial Specialization
//
using RCPBasic = SymEngine::RCP<const SymEngine::Basic>;

template<size_t N, size_t M>
class Zeros<RCPBasic, N, M> : public Matrix<Zeros<RCPBasic, N, M>> {
private:

public:
  Zeros();

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline std::vector<RCPBasic> as_vec() const;
  inline DenseMatrix<RCPBasic> as_dense() const;

  inline RCPBasic operator[](const size_t pos);
  inline const RCPBasic operator[](const size_t pos) const;

  inline RCPBasic operator()(const size_t row, const size_t col);
  inline const RCPBasic operator()(const size_t row, const size_t col) const;
};

template<size_t N, size_t M>
Zeros<RCPBasic, N, M>::Zeros() {
  //
}

template<size_t N, size_t M>
inline size_t Zeros<RCPBasic, N, M>::size() const {
  return N*M;
}

template<size_t N, size_t M>
inline size_t Zeros<RCPBasic, N, M>::capacity() const {
  return 0;
}

template<size_t N, size_t M>
inline bool Zeros<RCPBasic, N, M>::empty() const {
  return false;
}

template<size_t N, size_t M>
inline size_t Zeros<RCPBasic, N, M>::nrows() const {
  return N;
}

template<size_t N, size_t M>
inline size_t Zeros<RCPBasic, N, M>::ncols() const {
  return M;
}

template<size_t N, size_t M>
inline std::vector<RCPBasic>
Zeros<RCPBasic, N, M>::as_vec() const {
  std::vector<RCPBasic> v(N*M, SymEngine::zero);

  return v;
}

template<size_t N, size_t M>
inline DenseMatrix<RCPBasic> Zeros<RCPBasic, N, M>::as_dense() const {
  std::vector<RCPBasic> v = (*this).as_vec();
  
  return DenseMatrix<RCPBasic>(N, M, v);
}

template<size_t N, size_t M>
inline RCPBasic
Zeros<RCPBasic, N, M>::operator[](const size_t pos) {
  return SymEngine::zero;
}

template<size_t N, size_t M>
inline const RCPBasic
Zeros<RCPBasic, N, M>::operator[](const size_t pos) const {
  return SymEngine::zero;
}

template<size_t N, size_t M>
inline RCPBasic
Zeros<RCPBasic, N, M>::operator()(const size_t row,
                                  const size_t col) {
  return SymEngine::zero;
}

template<size_t N, size_t M>
inline const RCPBasic
Zeros<RCPBasic, N, M>::operator()(const size_t row,
                                  const size_t col) const {
  return SymEngine::zero;
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_CONSTANT_ZEROS_HPP */
