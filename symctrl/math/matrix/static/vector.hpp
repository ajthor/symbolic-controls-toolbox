#ifndef SYMCTRL_MATH_MATRIX_STATIC_VECTOR_HPP
#define SYMCTRL_MATH_MATRIX_STATIC_VECTOR_HPP

#include <vector>

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/vector/vector.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// StaticVector
//
template<typename T, size_t N, size_t M>
class StaticVector : public Matrix<StaticVector<T, N, M>> {
public:
  using type = T;

  using result_type = Vector<T>;

private:
  std::vector<T> v_;

public:
  explicit inline StaticVector();
  explicit inline StaticVector(const std::vector<T> v);

  inline StaticVector(const Vector<T> &m);
  inline StaticVector(const StaticVector<T, N, M> &m);

  template<typename DT>
  inline StaticVector(const Matrix<DT> &m);

  inline StaticVector<T, N, M> &operator=(const T &rhs);
  inline StaticVector<T, N, M> &operator=(const StaticVector<T, N, M> &rhs);

  template<typename DT>
  inline StaticVector<T, N, M> &operator=(const Matrix<DT> &rhs);

  inline StaticVector<T, N, M> &operator+=(const T &rhs);
  inline StaticVector<T, N, M> &operator-=(const T &rhs);
  inline StaticVector<T, N, M> &operator*=(const T &rhs);
  inline StaticVector<T, N, M> &operator/=(const T &rhs);

  template<typename DT>
  inline StaticVector<T, N, M> &operator+=(const Matrix<DT> &rhs);
  template<typename DT>
  inline StaticVector<T, N, M> &operator-=(const Matrix<DT> &rhs);

  template<typename DT>
  inline void apply(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_add(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_sub(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_mul(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_inverse(const Matrix<DT> &rhs);
  template<typename DT>
  inline void apply_transpose(const Matrix<DT> &rhs);

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline typename std::vector<T>::iterator begin();
  inline typename std::vector<T>::iterator end();
  inline typename std::vector<T>::const_iterator begin() const;
  inline typename std::vector<T>::const_iterator end() const;
  inline typename std::vector<T>::const_iterator cbegin() const;
  inline typename std::vector<T>::const_iterator cend() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline std::vector<T> as_vec() const;

  inline T &operator[](const size_t pos);
  inline const T &operator[](const size_t pos) const;

  inline T &operator()(const size_t pos);
  inline const T &operator()(const size_t pos) const;

  SYMCTRL_STATIC_ASSERT(N != 0 && M != 0,
    "StaticVector must have N != 0 && M != 0")
  SYMCTRL_STATIC_ASSERT(N == 1 || M == 1,
    "StaticVector must have N == 1 || M == 1");
};

// ----------------------------------------------------------------------
// StaticVector Constructor
//
template<typename T, size_t N, size_t M>
StaticVector<T, N, M>::StaticVector() {
  //
  v_ = std::vector<T>(N*M);
}

template<typename T, size_t N, size_t M>
StaticVector<T, N, M>::StaticVector(const std::vector<T> v) :
                                    v_(v) {
  //
  SYMCTRL_ASSERT(v.size() == N*M);
}

template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M>::StaticVector(const Vector<T> &m) :
                                           v_(m.as_vec()) {
  //
  SYMCTRL_ASSERT(N == m.nrows());
  SYMCTRL_ASSERT(M == m.ncols());
}

template<typename T, size_t N, size_t M>
StaticVector<T, N, M>::StaticVector(const StaticVector<T, N, M> &m) :
                                    v_(m.v_) {
  //
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline StaticVector<T, N, M>::StaticVector(const Matrix<DT> &m) :
                                           v_((~m).as_vec()) {
  //
  SYMCTRL_ASSERT(N == (~m).nrows());
  SYMCTRL_ASSERT(M == (~m).ncols());
}

// ----------------------------------------------------------------------
// StaticVector Assignment Operator
//
template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M>&
StaticVector<T, N, M>::operator=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M>&
StaticVector<T, N, M>::operator=(const StaticVector<T, N, M> &rhs) {
  v_ = rhs.v_;

  return *this;
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline StaticVector<T, N, M>&
StaticVector<T, N, M>::operator=(const Matrix<DT> &rhs) {
  apply_(*this, ~rhs);

  return *this;
}

// ----------------------------------------------------------------------
// StaticVector Member Function Definitions
//
template<typename T, size_t N, size_t M>
inline size_t StaticVector<T, N, M>::size() const {
  return N*M;
}

template<typename T, size_t N, size_t M>
inline size_t StaticVector<T, N, M>::capacity() const {
  return v_.capacity();
}

template<typename T, size_t N, size_t M>
inline bool StaticVector<T, N, M>::empty() const {
  return v_.empty();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::iterator
StaticVector<T, N, M>::begin() {
  return v_.begin();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::iterator
StaticVector<T, N, M>::end() {
  return v_.end();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::const_iterator
StaticVector<T, N, M>::begin() const {
  return v_.begin();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::const_iterator
StaticVector<T, N, M>::end() const {
  return v_.end();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::const_iterator
StaticVector<T, N, M>::cbegin() const {
  return v_.cbegin();
}

template<typename T, size_t N, size_t M>
inline typename std::vector<T>::const_iterator
StaticVector<T, N, M>::cend() const {
  return v_.cend();
}

template<typename T, size_t N, size_t M>
inline size_t StaticVector<T, N, M>::nrows() const {
  return N;
}

template<typename T, size_t N, size_t M>
inline size_t StaticVector<T, N, M>::ncols() const {
  return M;
}

template<typename T, size_t N, size_t M>
inline std::vector<T> StaticVector<T, N, M>::as_vec() const {
  return v_;
}

template<typename T, size_t N, size_t M>
inline T &StaticVector<T, N, M>::operator[](const size_t pos) {
  return v_[pos];
}

template<typename T, size_t N, size_t M>
inline const T &StaticVector<T, N, M>::operator[](const size_t pos) const {
  return v_[pos];
}

template<typename T, size_t N, size_t M>
inline T &StaticVector<T, N, M>::operator()(const size_t pos) {
  return v_[pos];
}

template<typename T, size_t N, size_t M>
inline const T &StaticVector<T, N, M>::operator()(const size_t pos) const {
  return v_[pos];
}

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_STATIC_VECTOR_HPP */
