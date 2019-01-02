#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_DENSE_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_DENSE_HPP

#include <vector>

#include <symctrl/math/matrix/dense/dense.hpp>
#include <symctrl/math/matrix/expression/symbolic.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// DenseMatrix Expressions
//
template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator+=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] += rhs;
  }

  return *this;
}

template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator-=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] -= rhs;
  }

  return *this;
}

template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator*=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] *= rhs;
  }

  return *this;
}

template<typename T>
inline DenseMatrix<T> &DenseMatrix<T>::operator/=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] /= rhs;
  }

  return *this;
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply(const Matrix<DT> &rhs) {
  n_ = (~rhs).nrows();
  m_ = (~rhs).ncols();
  v_ = (~rhs).as_vec();
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_add(const Matrix<DT> &rhs) {
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
inline void DenseMatrix<T>::apply_sub(const Matrix<DT> &rhs) {
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
inline void DenseMatrix<T>::apply_mul(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT((~rhs).nrows() == (~rhs).ncols());

  std::vector<T> t_(n_*(~rhs).ncols(), 0);

  for(size_t i = 0; i < n_; i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {

      for(size_t k = 0; k < m_; k++) {
        t_[i*(~rhs).ncols() + j] += v_[i*m_ + k] * (~rhs)[k*(~rhs).ncols() + j];
      }
    }
  }

  m_ = (~rhs).ncols();
  v_ = t_;
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_inverse(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(v_.size() == (~rhs).size());

  std::vector<T> t_((~rhs).size());

  for(size_t i = 0; i < (~rhs).nrows(); i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {
      t_[j*(~rhs).nrows() + i] = (~rhs)[i*(~rhs).ncols() + j];
    }
  }

  size_t tmp = (~rhs).nrows();
  n_ = (~rhs).ncols();
  m_ = tmp;
  v_ = t_;
}

template<typename T>
template<typename DT>
inline void DenseMatrix<T>::apply_transpose(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(v_.size() == (~rhs).size());

  std::vector<T> t_((~rhs).size());

  for(size_t i = 0; i < (~rhs).nrows(); i++) {
    for(size_t j = 0; j < (~rhs).ncols(); j++) {
      t_[j*(~rhs).nrows() + i] = (~rhs)[i*(~rhs).ncols() + j];
    }
  }

  size_t tmp = (~rhs).nrows();
  n_ = (~rhs).ncols();
  m_ = tmp;
  v_ = t_;
}

// ----------------------------------------------------------------------
// DenseMatrix Equal
//
template<typename T>
inline bool equal(const DenseMatrix<T> &lhs, const DenseMatrix<T> &rhs) {
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

// ----------------------------------------------------------------------
// SymbolicDense Specialization
//
using SymbolicDense = DenseMatrix<RCPBasic>;

template<>
inline SymbolicDense&
SymbolicDense::operator+=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::add(v_[i], rhs);
  }

  return *this;
}

template<>
inline SymbolicDense&
SymbolicDense::operator-=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::sub(v_[i], rhs);
  }

  return *this;
}

template<>
inline SymbolicDense&
SymbolicDense::operator*=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::mul(v_[i], rhs);
  }

  return *this;
}

template<>
inline SymbolicDense&
SymbolicDense::operator/=(const RCPBasic &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] = SymEngine::div(v_[i], rhs);
  }

  return *this;
}

template<>
template<>
inline void SymbolicDense::apply_add(const Matrix<SymbolicDense> &rhs) {
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
inline void SymbolicDense::apply_sub(const Matrix<SymbolicDense> &rhs) {
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
inline void SymbolicDense::apply_mul(const Matrix<SymbolicDense> &rhs) {
  SYMCTRL_ASSERT(m_ == (~rhs).n_);

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
// SymbolicDense Equal
//
template<>
inline bool equal(const SymbolicDense &lhs, const SymbolicDense &rhs) {
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

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_EXPRESSION_DENSE_HPP */
