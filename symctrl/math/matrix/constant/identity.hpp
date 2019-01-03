#ifndef SYMCTRL_MATH_MATRIX_CONSTANT_IDENTITY_HPP
#define SYMCTRL_MATH_MATRIX_CONSTANT_IDENTITY_HPP

#include <vector>

#include <symengine/basic.h>
#include <symengine/constants.h>

#include <symctrl/math/matrix/dense/dense.hpp>
#include <symctrl/math/matrix/static/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Identity
//
template<typename T, size_t N, size_t M>
class Identity : public Matrix<Identity<T, N, M>> {
public:
  using type = T;

  using result_type = DenseMatrix<T>;

private:

public:
  Identity();

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline std::vector<T> as_vec() const;
  inline StaticDense<T, N, M> as_dense() const;

  inline T operator[](const size_t pos);
  inline const T operator[](const size_t pos) const;

  inline T operator()(const size_t row, const size_t col);
  inline const T operator()(const size_t row, const size_t col) const;
};

template<typename T, size_t N, size_t M>
Identity<T, N, M>::Identity() {
  //
}

template<typename T, size_t N, size_t M>
inline size_t Identity<T, N, M>::size() const {
  return N*M;
}

template<typename T, size_t N, size_t M>
inline size_t Identity<T, N, M>::capacity() const {
  return 0;
}

template<typename T, size_t N, size_t M>
inline bool Identity<T, N, M>::empty() const {
  return false;
}

template<typename T, size_t N, size_t M>
inline size_t Identity<T, N, M>::nrows() const {
  return N;
}

template<typename T, size_t N, size_t M>
inline size_t Identity<T, N, M>::ncols() const {
  return M;
}

template<typename T, size_t N, size_t M>
inline std::vector<T> Identity<T, N, M>::as_vec() const {
  std::vector<T> v(N*M, T(0));
  for(size_t i = 0; i < std::min(N, M); i++) {
    v[i*M + i] = T(1);
  }

  return v;
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M> Identity<T, N, M>::as_dense() const {
  std::vector<T> v = (*this).as_vec();

  return StaticDense<T, N, M>(v);
}

template<typename T, size_t N, size_t M>
inline T Identity<T, N, M>::operator[](const size_t pos) {
  return (pos%(M + 1) == 0) ? T(1) : T(0);
}

template<typename T, size_t N, size_t M>
inline const T Identity<T, N, M>::operator[](const size_t pos) const {
  return (pos%(M + 1) == 0) ? T(1) : T(0);
}

template<typename T, size_t N, size_t M>
inline T Identity<T, N, M>::operator()(const size_t row,
                                       const size_t col) {
  return (row == col) ? T(1) : T(0);
}

template<typename T, size_t N, size_t M>
inline const T Identity<T, N, M>::operator()(const size_t row,
                                             const size_t col) const {
  return (row == col) ? T(1) : T(0);
}

// ----------------------------------------------------------------------
// Symbolic Partial Specialization
//
using RCPBasic = SymEngine::RCP<const SymEngine::Basic>;

template<size_t N, size_t M>
class Identity<RCPBasic, N, M> : public Matrix<Identity<RCPBasic, N, M>> {
private:

public:
  Identity();

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline std::vector<RCPBasic> as_vec() const;
  inline StaticDense<RCPBasic, N, M> as_dense() const;

  inline RCPBasic operator[](const size_t pos);
  inline const RCPBasic operator[](const size_t pos) const;

  inline RCPBasic operator()(const size_t row, const size_t col);
  inline const RCPBasic operator()(const size_t row, const size_t col) const;
};

template<size_t N, size_t M>
Identity<RCPBasic, N, M>::Identity() {
  //
}

template<size_t N, size_t M>
inline size_t Identity<RCPBasic, N, M>::size() const {
  return N*M;
}

template<size_t N, size_t M>
inline size_t Identity<RCPBasic, N, M>::capacity() const {
  return 0;
}

template<size_t N, size_t M>
inline bool Identity<RCPBasic, N, M>::empty() const {
  return false;
}

template<size_t N, size_t M>
inline size_t Identity<RCPBasic, N, M>::nrows() const {
  return N;
}

template<size_t N, size_t M>
inline size_t Identity<RCPBasic, N, M>::ncols() const {
  return M;
}

template<size_t N, size_t M>
inline std::vector<RCPBasic> Identity<RCPBasic, N, M>::as_vec() const {
  std::vector<RCPBasic> v(N*M, SymEngine::zero);
  for(size_t i = 0; i < std::min(N, M); i++) {
    v[i*M + i] = SymEngine::one;
  }

  return v;
}

template<size_t N, size_t M>
inline StaticDense<RCPBasic, N, M> Identity<RCPBasic, N, M>::as_dense() const {
  std::vector<RCPBasic> v = (*this).as_vec();

  return StaticDense<RCPBasic, N, M>(v);
}

template<size_t N, size_t M>
inline RCPBasic
Identity<RCPBasic, N, M>::operator[](const size_t pos) {
  return (pos%(M + 1) == 0) ? SymEngine::one : SymEngine::zero;
}

template<size_t N, size_t M>
inline const RCPBasic
Identity<RCPBasic, N, M>::operator[](const size_t pos) const {
  return (pos%(M + 1) == 0) ? SymEngine::one : SymEngine::zero;
}

template<size_t N, size_t M>
inline RCPBasic
Identity<RCPBasic, N, M>::operator()(const size_t row,
                                     const size_t col) {
  return (row == col) ? SymEngine::one : SymEngine::zero;
}

template<size_t N, size_t M>
inline const RCPBasic
Identity<RCPBasic, N, M>::operator()(const size_t row,
                                     const size_t col) const {
  return (row == col) ? SymEngine::one : SymEngine::zero;
}

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_CONSTANT_IDENTITY_HPP */
