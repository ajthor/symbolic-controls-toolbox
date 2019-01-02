#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_INVERSE_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_INVERSE_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/expression/expression.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprInverse
//
template<typename M>
class ExprInverse : public Expression<Matrix<ExprInverse<M>>> {
public:
  using type = typename M::type;

  using result_type = result_type_t<M>;

private:
  const M &m_;

public:
  explicit inline ExprInverse(const M &m);

  operator type() const;

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline type &operator[](const size_t pos);
  inline const type &operator[](const size_t pos) const;

private:
  // A^-1
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprInverse<M> &rhs) {
    SYMCTRL_DEBUG("result = A^-1");
    apply_inverse_(~lhs, rhs.m_);
  }

  // A + B^-1
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprInverse<M> &rhs) {
    SYMCTRL_DEBUG("result = A + B^-1");
    M tmp(rhs.m_);
    apply_inverse_(tmp, rhs.m_);
    apply_add_(~lhs, tmp);
  }

  // A - B^-1
  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprInverse<M> &rhs) {
    SYMCTRL_DEBUG("result = A - B^-1");
    M tmp(rhs.m_);
    apply_inverse_(tmp, rhs.m_);
    apply_sub_(~lhs, tmp);
  }

  // A * B^-1
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprInverse<M> &rhs) {
    SYMCTRL_DEBUG("result = A * B^-1");
    M tmp(rhs.m_);
    apply_inverse_(tmp, rhs.m_);
    apply_mul_(~lhs, tmp);
  }

  // (A^-1)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprInverse<M> &rhs) {
    SYMCTRL_DEBUG("result = (A^-1)^-1");
    apply_(~lhs, rhs.m_);
  }

  // (A^-1)^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprInverse<M> &rhs) {
    SYMCTRL_DEBUG("result = (A^-1)^T");
    M tmp(rhs.m_);
    apply_transpose_(tmp, rhs.m_);
    apply_inverse_(~lhs, tmp);
  }
};

// ----------------------------------------------------------------------
// ExprInverse Constructor
//
template<typename M>
inline ExprInverse<M>::ExprInverse(const M &m) :
                                   m_(m) {
  //
}

// ----------------------------------------------------------------------
// ExprInverse Type Conversion Operator
//
template<typename M>
ExprInverse<M>::operator ExprInverse<M>::type() const {
  result_type r;
  apply_inverse_(r, m_);

  SYMCTRL_ASSERT(r.nrows() == 1);
  SYMCTRL_ASSERT(r.ncols() == 1);

  return r[0];
}

// ----------------------------------------------------------------------
// ExprInverse Member Function Definitions
//
template<typename M>
inline size_t ExprInverse<M>::size() const {
  return m_.size();
}

template<typename M>
inline size_t ExprInverse<M>::capacity() const {
  return m_.capacity();
}

template<typename M>
inline bool ExprInverse<M>::empty() const {
  return m_.empty();
}

template<typename M>
inline size_t ExprInverse<M>::nrows() const {
  return m_.nrows();
}

template<typename M>
inline size_t ExprInverse<M>::ncols() const {
  return m_.ncols();
}

template<typename M>
inline typename ExprInverse<M>::type&
ExprInverse<M>::operator[](const size_t pos) {
  return m_[pos];
}

template<typename M>
inline const typename ExprInverse<M>::type&
ExprInverse<M>::operator[](const size_t pos) const {
  return m_[pos];
}

template<typename M>
inline const ExprInverse<M>
inverse(const Matrix<M> &m) {
  return ExprInverse<M>(~m);
}

} // Math
} // Controls

#endif /* end of include guard: SYMCTRL_MATH_MATRIX_EXPRESSION_INVERSE_HPP */
