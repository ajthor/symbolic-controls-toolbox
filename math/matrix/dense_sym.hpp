#ifndef MATH_MATRIX_DENSE_SYM_HPP
#define MATH_MATRIX_DENSE_SYM_HPP

#include <type_traits>

#include <symengine/add.h>
#include <symengine/mul.h>
#include <symengine/basic.h>
#include <symengine/constants.h>

#include "dense.hpp"

namespace Controls {
namespace Math {

using RCPBasic = SymEngine::RCP<const SymEngine::Basic>;
using SymbolicMatrix = DenseMatrix<RCPBasic>;

// ----------------------------------------------------------------------
// DenseMatrix Symbolic Specialization
//
template<>
inline SymbolicMatrix&
SymbolicMatrix::operator+=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::add(v_[i], rhs);
  }

  return *this;
}

template<>
inline SymbolicMatrix&
SymbolicMatrix::operator-=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::sub(v_[i], rhs);
  }

  return *this;
}

template<>
inline SymbolicMatrix&
SymbolicMatrix::operator*=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::mul(v_[i], rhs);
  }

  return *this;
}

template<>
inline SymbolicMatrix&
SymbolicMatrix::operator/=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::div(v_[i], rhs);
  }

  return *this;
}

template<>
template<>
inline void SymbolicMatrix::apply_add(const Matrix<SymbolicMatrix> &rhs) {
  MATRIX_ASSERT(n_ == (~rhs).n_);
  MATRIX_ASSERT(m_ == (~rhs).m_);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      v_[i*m_ + j] = SymEngine::add(v_[i*m_ + j], (~rhs)[i*m_ + j]);
    }
  }
}

template<>
template<>
inline void SymbolicMatrix::apply_mul(const Matrix<SymbolicMatrix> &rhs) {
  MATRIX_ASSERT(m_ == (~rhs).n_);

  std::vector<RCPBasic> t_(n_*(~rhs).m_, SymEngine::zero);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < (~rhs).m_; j++) {

      for(size_t k = 0; k < m_; k++) {
        t_[i*(~rhs).m_ + j] =
          SymEngine::add(t_[i*(~rhs).m_ + j],
            SymEngine::mul(v_[i*m_ + k], (~rhs)[k*(~rhs).m_ + j]));
      }
    }
  }

  m_ = (~rhs).m_;
  v_ = t_;
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_DENSE_SYM_HPP */
