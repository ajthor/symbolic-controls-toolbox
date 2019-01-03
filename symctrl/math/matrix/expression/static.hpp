#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_STATIC_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_STATIC_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/static/dense.hpp>
#include <symctrl/math/matrix/static/vector.hpp>
#include <symctrl/traits/is_static.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// StaticDense Expressions
//
template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M> &StaticDense<T, N, M>::operator+=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] += rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M> &StaticDense<T, N, M>::operator-=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] -= rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M> &StaticDense<T, N, M>::operator*=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] *= rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticDense<T, N, M> &StaticDense<T, N, M>::operator/=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] /= rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline void StaticDense<T, N, M>::apply(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(N == (~rhs).nrows());
  SYMCTRL_ASSERT(M == (~rhs).ncols());

  v_ = (~rhs).as_vec();
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline void StaticDense<T, N, M>::apply_add(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(N == (~rhs).nrows());
  SYMCTRL_ASSERT(M == (~rhs).ncols());

  for(size_t i = 0; i < N; i++) {
    for(size_t j = 0; j < M; j++) {
      v_[i*M + j] += (~rhs)[i*M + j];
    }
  }
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline void StaticDense<T, N, M>::apply_sub(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(N == (~rhs).nrows());
  SYMCTRL_ASSERT(M == (~rhs).ncols());

  for(size_t i = 0; i < N; i++) {
    for(size_t j = 0; j < M; j++) {
      v_[i*M + j] -= (~rhs)[i*M + j];
    }
  }
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline void StaticDense<T, N, M>::apply_mul(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(N == (~rhs).nrows());
  SYMCTRL_ASSERT(M == (~rhs).ncols());

  std::vector<T> t_(N*M, 0);

  for(size_t i = 0; i < N; i++) {
    for(size_t j = 0; j < M; j++) {

      for(size_t k = 0; k < M; k++) {
        t_[i*M + j] += v_[i*M + k] * (~rhs)[k*M + j];
      }
    }
  }

  v_ = t_;
}

// ----------------------------------------------------------------------
// StaticDense Equal
//
template<typename T, size_t N, size_t M>
inline bool equal(const StaticDense<T, N, M> &lhs,
                  const StaticDense<T, N, M> &rhs) {
  for(size_t i = 0; i < N; i++) {
    for(size_t j = 0; j < M; j++) {
      if(!equal((~lhs)(i, j), (~rhs)(i, j)))
        return false;
    }
  }

  return true;
}

template<typename DT, typename T, size_t N, size_t M>
inline auto equal(const Matrix<DT> &lhs, const StaticDense<T, N, M> &rhs)
-> disable_if_static_t<DT, bool> {
  if((~lhs).nrows() != N || (~lhs).ncols() != M) {
    return false;
  }

  for(size_t i = 0; i < (~rhs).size(); i++) {
    if(!equal((~lhs)[i], (~rhs)[i]))
      return false;
  }

  return true;
}

// ----------------------------------------------------------------------
// StaticVector Expressions
//
template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M> &StaticVector<T, N, M>::operator+=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] += rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M> &StaticVector<T, N, M>::operator-=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] -= rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M> &StaticVector<T, N, M>::operator*=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] *= rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
inline StaticVector<T, N, M> &StaticVector<T, N, M>::operator/=(const T &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] /= rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline StaticVector<T, N, M>&
StaticVector<T, N, M>::operator+=(const Matrix<DT> &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] += rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline StaticVector<T, N, M>&
StaticVector<T, N, M>::operator-=(const Matrix<DT> &rhs) {
  for(size_t i = 0; i < v_.size(); i++) {
    v_[i] -= rhs;
  }

  return *this;
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline void StaticVector<T, N, M>::apply(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(N == (~rhs).nrows());
  SYMCTRL_ASSERT(M == (~rhs).ncols());

  v_ = (~rhs).as_vec();
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline void StaticVector<T, N, M>::apply_add(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(N == (~rhs).nrows());
  SYMCTRL_ASSERT(M == (~rhs).ncols());

  for(size_t i = 0; i < N; i++) {
    for(size_t j = 0; j < M; j++) {
      v_[i*M + j] += (~rhs)[i*M + j];
    }
  }
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline void StaticVector<T, N, M>::apply_sub(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(N == (~rhs).nrows());
  SYMCTRL_ASSERT(M == (~rhs).ncols());

  for(size_t i = 0; i < N; i++) {
    for(size_t j = 0; j < M; j++) {
      v_[i*M + j] -= (~rhs)[i*M + j];
    }
  }
}

template<typename T, size_t N, size_t M>
template<typename DT>
inline void StaticVector<T, N, M>::apply_mul(const Matrix<DT> &rhs) {
  SYMCTRL_ASSERT(N == (~rhs).nrows());
  SYMCTRL_ASSERT(M == (~rhs).ncols());

  std::vector<T> t_(N*M, 0);

  for(size_t i = 0; i < N; i++) {
    for(size_t j = 0; j < M; j++) {

      for(size_t k = 0; k < M; k++) {
        t_[i*M + j] += v_[i*M + k] * (~rhs)[k*M + j];
      }
    }
  }

  v_ = t_;
}

// ----------------------------------------------------------------------
// StaticVector Equal
//
template<typename T, size_t N, size_t M>
inline bool equal(const StaticVector<T, N, M> &lhs,
                  const StaticVector<T, N, M> &rhs) {
  for(size_t i = 0; i < N*M; i++) {
    if(!equal((~lhs)[i], (~rhs)[i]))
      return false;
  }

  return true;
}

template<typename DT, typename T, size_t N, size_t M>
inline auto equal(const Matrix<DT> &lhs, const StaticVector<T, N, M> &rhs)
-> disable_if_static_t<DT, bool> {
  if((~lhs).nrows() != N || (~lhs).ncols() != M) {
    return false;
  }

  for(size_t i = 0; i < N*M; i++) {
    if(!equal((~lhs)[i], (~rhs)[i]))
      return false;
  }

  return true;
}

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_EXPRESSION_STATIC_HPP */
