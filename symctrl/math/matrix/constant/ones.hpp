#ifndef SYMCTRL_MATH_MATRIX_CONSTANT_ONES_HPP
#define SYMCTRL_MATH_MATRIX_CONSTANT_ONES_HPP

#include <vector>

#include <symengine/basic.h>
#include <symengine/constants.h>

#include <symctrl/math/matrix/dense/dense.hpp>
#include <symctrl/math/matrix/static/dense.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Ones
//
template<typename T, size_t N, size_t M>
class Ones : public Matrix<Ones<T, N, M>> {
public:
  using type = T;

  using result_type = DenseMatrix<T>;

private:

public:
  Ones();

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
Ones<T, N, M>::Ones() {
  //
}

template<typename T, size_t N, size_t M>
inline size_t Ones<T, N, M>::size() const {
  return N*M;
}

template<typename T, size_t N, size_t M>
inline size_t Ones<T, N, M>::capacity() const {
  return 0;
}

template<typename T, size_t N, size_t M>
inline bool Ones<T, N, M>::empty() const {
  return false;
}

template<typename T, size_t N, size_t M>
inline size_t Ones<T, N, M>::nrows() const {
  return N;
}

template<typename T, size_t N, size_t M>
inline size_t Ones<T, N, M>::ncols() const {
  return M;
}

template<typename T, size_t N, size_t M>
inline std::vector<T> Ones<T, N, M>::as_vec() const {
  std::vector<T> v(N*M, T(1));

  return v;
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M> Ones<T, N, M>::as_dense() const {
  std::vector<T> v = (*this).as_vec();

  return StaticDense<T, N, M>(v);
}

template<typename T, size_t N, size_t M>
inline T Ones<T, N, M>::operator[](const size_t pos) {
  return T(1);
}

template<typename T, size_t N, size_t M>
inline const T Ones<T, N, M>::operator[](const size_t pos) const {
  return T(1);
}

template<typename T, size_t N, size_t M>
inline T Ones<T, N, M>::operator()(const size_t row,
                                   const size_t col) {
  return T(1);
}

template<typename T, size_t N, size_t M>
inline const T Ones<T, N, M>::operator()(const size_t row,
                                         const size_t col) const {
  return T(1);
}

// ----------------------------------------------------------------------
// Symbolic Partial Specialization
//
using RCPBasic = SymEngine::RCP<const SymEngine::Basic>;

template<size_t N, size_t M>
class Ones<RCPBasic, N, M> : public Matrix<Ones<RCPBasic, N, M>> {
private:

public:
  Ones();

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
Ones<RCPBasic, N, M>::Ones() {
  //
}

template<size_t N, size_t M>
inline size_t Ones<RCPBasic, N, M>::size() const {
  return N*M;
}

template<size_t N, size_t M>
inline size_t Ones<RCPBasic, N, M>::capacity() const {
  return 0;
}

template<size_t N, size_t M>
inline bool Ones<RCPBasic, N, M>::empty() const {
  return false;
}

template<size_t N, size_t M>
inline size_t Ones<RCPBasic, N, M>::nrows() const {
  return N;
}

template<size_t N, size_t M>
inline size_t Ones<RCPBasic, N, M>::ncols() const {
  return M;
}

template<size_t N, size_t M>
inline std::vector<RCPBasic>
Ones<RCPBasic, N, M>::as_vec() const {
  std::vector<RCPBasic> v(N*M, SymEngine::one);

  return v;
}

template<size_t N, size_t M>
inline StaticDense<RCPBasic, N, M> Ones<RCPBasic, N, M>::as_dense() const {
  std::vector<RCPBasic> v = (*this).as_vec();

  return StaticDense<RCPBasic, N, M>(v);
}

template<size_t N, size_t M>
inline RCPBasic
Ones<RCPBasic, N, M>::operator[](const size_t pos) {
  return SymEngine::one;
}

template<size_t N, size_t M>
inline const RCPBasic
Ones<RCPBasic, N, M>::operator[](const size_t pos) const {
  return SymEngine::one;
}

template<size_t N, size_t M>
inline RCPBasic
Ones<RCPBasic, N, M>::operator()(const size_t row,
                                 const size_t col) {
  return SymEngine::one;
}

template<size_t N, size_t M>
inline const RCPBasic
Ones<RCPBasic, N, M>::operator()(const size_t row,
                                 const size_t col) const {
  return SymEngine::one;
}

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_CONSTANT_ONES_HPP */
