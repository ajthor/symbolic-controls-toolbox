#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_NEG_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_NEG_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/expression/expression.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprNeg
//
template<typename M>
class ExprNeg : public Expression<Matrix<ExprNeg<M>>> {
public:
  using type = typename M::type;

  using result_type = result_type_t<M>;

private:
  const M m_;

public:
  explicit inline ExprNeg(const M &m);

  inline ExprNeg(const ExprNeg<M> &m);

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
  // -A
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    SYMCTRL_DEBUG("result = -A");
    apply_(~lhs, rhs.m_);
    ~lhs *= -1;
  }

  // A + -B
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    SYMCTRL_DEBUG("result = A + -B");
    apply_sub_(~lhs, rhs.m_);
  }

  // A - -B
  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    SYMCTRL_DEBUG("result = A - -B");
    apply_add_(~lhs, rhs.m_);
  }

  // A * -B
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    SYMCTRL_DEBUG("result = A * -B");
    apply_mul_(~lhs, rhs.m_);
    ~lhs *= -1;
  }

  // (-A)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    SYMCTRL_DEBUG("result = (-A)^-1");
    apply_inverse_(~lhs, rhs.m_);
    ~lhs *= -1;
  }

  // (-A)^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprNeg<M> &rhs) {
    SYMCTRL_DEBUG("result = (-A)^T");
    apply_transpose_(~lhs, rhs.m_);
    ~lhs *= -1;
  }
};

// ----------------------------------------------------------------------
// ExprNeg Constructor
//
template<typename M>
inline ExprNeg<M>::ExprNeg(const M &m) :
                           m_(m) {
  //
}

template<typename M>
inline ExprNeg<M>::ExprNeg(const ExprNeg<M> &m) :
                           m_(m.m_) {
  //
}

template<typename M>
inline const M ExprNeg<M>::get_operand() {
  return m_;
}

// ----------------------------------------------------------------------
// ExprNeg Type Conversion Operator
//
template<typename M>
ExprNeg<M>::operator ExprNeg<M>::type() const {
  result_type r;
  apply_(r, m_);
  r *= -1;

  SYMCTRL_ASSERT(r.nrows() == 1);
  SYMCTRL_ASSERT(r.ncols() == 1);

  return r[0];
}

// ----------------------------------------------------------------------
// ExprNeg Member Function Definitions
//
template<typename M>
inline size_t ExprNeg<M>::size() const {
  return m_.size();
}

template<typename M>
inline size_t ExprNeg<M>::capacity() const {
  return m_.capacity();
}

template<typename M>
inline bool ExprNeg<M>::empty() const {
  return m_.empty();
}

template<typename M>
inline size_t ExprNeg<M>::nrows() const {
  return m_.nrows();
}

template<typename M>
inline size_t ExprNeg<M>::ncols() const {
  return m_.ncols();
}

template<typename M>
inline typename ExprNeg<M>::type&
ExprNeg<M>::operator[](const size_t pos) {
  return -m_[pos];
}

template<typename M>
inline const typename ExprNeg<M>::type&
ExprNeg<M>::operator[](const size_t pos) const {
  return -m_[pos];
}

// ----------------------------------------------------------------------
// ExprNeg Operator
//
template<typename M>
inline const ExprNeg<M>
operator-(const Matrix<M> &m) {
  return ExprNeg<M>(~m);
}

template<typename M>
inline const M
operator-(const ExprNeg<M> &m) {
  return m.get_operand();
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_NEG_HPP
