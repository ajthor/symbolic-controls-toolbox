#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_VECTOR_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_VECTOR_HPP

#include <type_traits>
#include <vector>

#include <symctrl/math/matrix/vector/vector.hpp>
#include <symctrl/math/matrix/expression/symbolic.hpp>
#include <symctrl/math/matrix/expression/transpose.hpp>
#include <symctrl/traits/is_scalar.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// Vector Expressions
//
template<typename T>
inline Vector<T> &Vector<T>::operator+=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] += rhs;
  }

  return *this;
}

template<typename T>
inline Vector<T> &Vector<T>::operator-=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] -= rhs;
  }

  return *this;
}

template<typename T>
inline Vector<T> &Vector<T>::operator*=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] *= rhs;
  }

  return *this;
}

template<typename T>
inline Vector<T> &Vector<T>::operator/=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] /= rhs;
  }

  return *this;
}

template<typename T>
template<typename DT>
inline Vector<T> &Vector<T>::operator+=(const Matrix<DT> &rhs) {
  apply_add_(*this, ~rhs);
  return *this;
}

template<typename T>
template<typename DT>
inline Vector<T> &Vector<T>::operator-=(const Matrix<DT> &rhs) {
  apply_sub_(*this, ~rhs);
  return *this;
}

template<typename T>
template<typename DT>
inline void Vector<T>::apply(const Matrix<DT> &rhs) {
  n_ = (~rhs).nrows();
  m_ = (~rhs).ncols();
  v_ = (~rhs).as_vec();
}

template<typename T>
template<typename DT>
inline void Vector<T>::apply_add(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(n_ == (~rhs).nrows());
  SYMCTRL_ASSERT(m_ == (~rhs).ncols());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      v_[i*m_ + j] += (~rhs)[i*m_ + j];
    }
  }
}

template<typename T>
template<typename DT>
inline void Vector<T>::apply_sub(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(n_ == (~rhs).nrows());
  SYMCTRL_ASSERT(m_ == (~rhs).ncols());

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      v_[i*m_ + j] -= (~rhs)[i*m_ + j];
    }
  }
}

template<typename T>
template<typename DT>
inline void Vector<T>::apply_mul(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(m_ == (~rhs).nrows());

  std::vector<T> t_(n_*(~rhs).ncols(), 0);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {

      for(size_t k = 0; k < m_; k++) {
        t_[i*(~rhs).ncols() + j] +=
          v_[i*m_ + k] * (~rhs)[k*(~rhs).ncols() + j];
      }
    }
  }

  m_ = (~rhs).ncols();
  v_ = t_;
}

template<typename T>
template<typename DT>
inline void Vector<T>::apply_transpose(const Matrix<DT> &rhs) {
  size_t tmp = (~rhs).nrows();
  n_ = (~rhs).ncols();
  m_ = tmp;
  v_ = (~rhs).as_vec();
}

// ----------------------------------------------------------------------
// Vector Equal
//
template<typename T>
inline bool equal(const Vector<T> &lhs, const Vector<T> &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~lhs).size(); i++) {
    if(!equal((~lhs)[i], (~rhs)[i]))
      return false;
  }

  return true;
}

template<typename DT, typename T>
inline bool equal(const Matrix<DT> &lhs, const Vector<T> &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~rhs).size(); i++) {
    if(!equal((~lhs)[i], (~rhs)[i]))
      return false;
  }

  return true;
}

// ----------------------------------------------------------------------
// SymbolicVector Specialization
//
using SymbolicVector = Vector<RCPBasic>;

template<>
inline SymbolicVector&
SymbolicVector::operator+=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::add(v_[i], rhs);
  }

  return *this;
}

template<>
inline SymbolicVector&
SymbolicVector::operator-=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::sub(v_[i], rhs);
  }

  return *this;
}

template<>
inline SymbolicVector&
SymbolicVector::operator*=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::mul(v_[i], rhs);
  }

  return *this;
}

template<>
inline SymbolicVector&
SymbolicVector::operator/=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::div(v_[i], rhs);
  }

  return *this;
}

template<>
template<>
inline void SymbolicVector::apply_add(const Matrix<SymbolicVector> &rhs) {
  SYMCTRL_ASSERT(n_ == (~rhs).n_);
  SYMCTRL_ASSERT(m_ == (~rhs).m_);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      v_[i*m_ + j] = SymEngine::add(v_[i*m_ + j], (~rhs)[i*m_ + j]);
    }
  }
}

template<>
template<>
inline void SymbolicVector::apply_sub(const Matrix<SymbolicVector> &rhs) {
  SYMCTRL_ASSERT(n_ == (~rhs).n_);
  SYMCTRL_ASSERT(m_ == (~rhs).m_);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      v_[i*m_ + j] = SymEngine::sub(v_[i*m_ + j], (~rhs)[i*m_ + j]);
    }
  }
}

template<>
template<>
inline void SymbolicVector::apply_mul(const Matrix<SymbolicVector> &rhs) {
  SYMCTRL_ASSERT(m_ == (~rhs).n_);

  std::vector<RCPBasic> t_(n_*(~rhs).m_, SymEngine::zero);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < (~rhs).m_; j++) {

      for(size_t k = 0; k < m_; k++) {
        t_[i*(~rhs).m_ + j] = SymEngine::add(t_[i*(~rhs).m_ + j], SymEngine::mul(v_[i*m_ + k], (~rhs)[k*(~rhs).m_ + j]));
      }
    }
  }

  m_ = (~rhs).m_;
  v_ = t_;
}

// ----------------------------------------------------------------------
// SymbolicVector Equal
//
template<>
inline bool equal(const SymbolicVector &lhs, const SymbolicVector &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~lhs).size(); i++) {
    if(!equal((~lhs)[i], (~rhs)[i]))
      return false;
  }

  return true;
}

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_EXPRESSION_VECTOR_HPP */
