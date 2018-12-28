#ifndef MATH_MATRIX_SYMBOLIC_DENSE_HPP
#define MATH_MATRIX_SYMBOLIC_DENSE_HPP

#include "dense.hpp"
#include "symbolic.hpp"

namespace Controls {
namespace Math {

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
inline void SymbolicMatrix::apply_sub(const Matrix<SymbolicMatrix> &rhs) {
  MATRIX_ASSERT(n_ == (~rhs).n_);
  MATRIX_ASSERT(m_ == (~rhs).m_);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < m_; j++) {
      v_[i*m_ + j] = SymEngine::sub(v_[i*m_ + j], (~rhs)[i*m_ + j]);
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

// ----------------------------------------------------------------------
// SymbolicMatrix Equal
//
template<>
inline bool equal(const SymbolicMatrix &lhs, const SymbolicMatrix &rhs) {
  if((~lhs).nrows() != (~rhs).nrows() || (~lhs).ncols() != (~rhs).ncols()) {
    return false;
  }

  for(size_t i = 0; i < (~lhs).nrows(); i++) {
    for(size_t j = 0; j < (~lhs).ncols(); j++) {
      if(!equal((~lhs)(i, j), (~rhs)(i, j)))
        return false;
    }
  }

  return true;
}

} // Math
} // Controls

#endif /* end of include guard: MATH_MATRIX_SYMBOLIC_DENSE_HPP */
