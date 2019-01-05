#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_UNARY_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_UNARY_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/expression/expression.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprUnary
//
template<typename M>
class ExprUnary : public Expression<Matrix<ExprUnary<M>>> {
public:
  using type = typename M::type;

  using result_type = result_type_t<M>;

private:
  const M m_;

public:
  explicit inline ExprUnary(const M &m);

  inline ExprUnary(const ExprUnary<M> &m);

  inline const M get_operand();

  operator type() const;

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline type &operator[](const size_t pos);
  inline const type &operator[](const size_t pos) const;

private:
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_add_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_sub_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_mul_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_inverse_(~lhs, rhs.m_);
  }

  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprUnary<M> &rhs) {
    apply_transpose_(~lhs, rhs.m_);
  }
};

// ----------------------------------------------------------------------
// ExprUnary Constructor
//
template<typename M>
inline ExprUnary<M>::ExprUnary(const M &m) :
                               m_(m) {
  //
}

template<typename M>
inline ExprUnary<M>::ExprUnary(const ExprUnary<M> &m) :
                               m_(m.m_) {
  //
}

template<typename M>
inline const M ExprUnary<M>::get_operand() {
  return m_;
}

// ----------------------------------------------------------------------
// ExprUnary Type Conversion Operator
//
template<typename M>
ExprUnary<M>::operator ExprUnary<M>::type() const {
  result_type r;
  apply_(r, *this);

  SYMCTRL_ASSERT(r.nrows() == 1);
  SYMCTRL_ASSERT(r.ncols() == 1);

  return r[0];
}

// ----------------------------------------------------------------------
// ExprUnary Member Function Definitions
//
template<typename M>
inline size_t ExprUnary<M>::size() const {
  return m_.size();
}

template<typename M>
inline size_t ExprUnary<M>::capacity() const {
  return m_.capacity();
}

template<typename M>
inline bool ExprUnary<M>::empty() const {
  return m_.empty();
}

template<typename M>
inline size_t ExprUnary<M>::nrows() const {
  return m_.nrows();
}

template<typename M>
inline size_t ExprUnary<M>::ncols() const {
  return m_.ncols();
}

template<typename M>
inline typename ExprUnary<M>::type&
ExprUnary<M>::operator[](const size_t pos) {
  return m_[pos];
}

template<typename M>
inline const typename ExprUnary<M>::type&
ExprUnary<M>::operator[](const size_t pos) const {
  return m_[pos];
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_UNARY_HPP
