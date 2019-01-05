#ifndef SYMCTRL_MATH_MATRIX_EXPRESSION_ADD_HPP
#define SYMCTRL_MATH_MATRIX_EXPRESSION_ADD_HPP

#include <symctrl/assert.hpp>
#include <symctrl/math/matrix/matrix.hpp>
#include <symctrl/math/matrix/expression/expression.hpp>
#include <symctrl/math/matrix/expression/unary.hpp>
#include <symctrl/type_traits/is_scalar.hpp>
#include <symctrl/math/matrix/type_traits/is_expr.hpp>

namespace Controls {
namespace Math {

// ----------------------------------------------------------------------
// ExprAdd
//
template<typename M1, typename M2>
class ExprAdd : public Expression<Matrix<ExprAdd<M1, M2>>> {
public:
  using type = typename M1::type;

  using result_type = result_type_t<M1>;

private:
  const M1 lhs_;
  const M2 rhs_;

public:
  explicit inline ExprAdd(const M1 &lhs, const M2 &rhs);

  inline ExprAdd(const ExprAdd<M1, M2> &m);

  operator type() const;

  inline size_t size() const;
  inline size_t capacity() const;

  inline bool empty() const;

  inline size_t nrows() const;
  inline size_t ncols() const;

  inline type &operator[](const size_t pos);
  inline const type &operator[](const size_t pos) const;

private:
  // A + B
  template<typename DT>
  friend inline void
  apply_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    SYMCTRL_DEBUG("result = A + B");
    if(!is_expr<M1>::value && equal(~lhs, rhs.lhs_)) {
      apply_add_(~lhs, rhs.rhs_);
    }
    else if(!is_expr<M2>::value && equal(~lhs, rhs.rhs_)) {
      apply_add_(~lhs, rhs.lhs_);
    }
    else {
      apply_(~lhs, rhs.lhs_);
      apply_add_(~lhs, rhs.rhs_);
    }
  }

  // A + (B + C)
  template<typename DT>
  friend inline void
  apply_add_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    SYMCTRL_DEBUG("result = A + (B + C)");
    apply_add_(~lhs, rhs.lhs_);
    apply_add_(~lhs, rhs.rhs_);
  }

  // A - (B + C)
  template<typename DT>
  friend inline void
  apply_sub_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    SYMCTRL_DEBUG("result = A - (B + C)");
    apply_sub_(~lhs, rhs.lhs_);
    apply_sub_(~lhs, rhs.rhs_);
  }

  // A * (B + C)
  template<typename DT>
  friend inline void
  apply_mul_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    SYMCTRL_DEBUG("result = A * (B + C)");
    M1 tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_mul_(~lhs, tmp);
  }

  // (A + B)^-1
  template<typename DT>
  friend inline void
  apply_inverse_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    SYMCTRL_DEBUG("result = (A + B)^-1");
    M1 tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_inverse_(~lhs, tmp);
  }

  // (A + B)^T = A^T + B^T
  template<typename DT>
  friend inline void
  apply_transpose_(Matrix<DT> &lhs, const ExprAdd<M1, M2> &rhs) {
    SYMCTRL_DEBUG("result = (A + B)^T");
    M1 tmp(rhs.lhs_);
    apply_add_(tmp, rhs.rhs_);
    apply_transpose_(~lhs, tmp);
  }
};

// ----------------------------------------------------------------------
// ExprAdd Constructor
//
template<typename M1, typename M2>
inline ExprAdd<M1, M2>::ExprAdd(const M1 &lhs,
                                const M2 &rhs) :
                                lhs_(lhs),
                                rhs_(rhs) {
  //
}

template<typename M1, typename M2>
inline ExprAdd<M1, M2>::ExprAdd(const ExprAdd<M1, M2> &m) :
                                lhs_(m.lhs_),
                                rhs_(m.rhs_) {
  //
}

// ----------------------------------------------------------------------
// ExprAdd Type Conversion Operator
//
template<typename M1, typename M2>
ExprAdd<M1, M2>::operator ExprAdd<M1, M2>::type() const {
  result_type r;
  apply_(r, *this);

  SYMCTRL_ASSERT(r.nrows() == 1);
  SYMCTRL_ASSERT(r.ncols() == 1);

  return r[0];
}

// ----------------------------------------------------------------------
// ExprAdd Member Function Definitions
//
template<typename M1, typename M2>
inline size_t ExprAdd<M1, M2>::size() const {
  return lhs_.size();
}

template<typename M1, typename M2>
inline size_t ExprAdd<M1, M2>::capacity() const {
  return lhs_.capacity();
}

template<typename M1, typename M2>
inline bool ExprAdd<M1, M2>::empty() const {
  return lhs_.empty();
}

template<typename M1, typename M2>
inline size_t ExprAdd<M1, M2>::nrows() const {
  return lhs_.nrows();
}

template<typename M1, typename M2>
inline size_t ExprAdd<M1, M2>::ncols() const {
  return lhs_.ncols();
}

template<typename M1, typename M2>
inline typename ExprAdd<M1, M2>::type&
ExprAdd<M1, M2>::operator[](const size_t pos) {
  return lhs_[pos] + rhs_[pos];
}

template<typename M1, typename M2>
inline const typename ExprAdd<M1, M2>::type&
ExprAdd<M1, M2>::operator[](const size_t pos) const {
  return lhs_[pos] + rhs_[pos];
}

// ----------------------------------------------------------------------
// ExprAdd Operator
//
template<typename M1, typename M2>
inline const ExprAdd<M1, M2>
operator+(const Matrix<M1> &lhs, const Matrix<M2> &rhs) {
  return ExprAdd<M1, M2>(~lhs, ~rhs);
}

// ----------------------------------------------------------------------
// ExprAdd Scalar Operator
//
template<typename M1, typename M2>
inline auto
operator+(const Matrix<M1> &lhs, const M2 rhs)
-> enable_if_scalar_t<M2, const ExprUnary<M1>> {
  M1 tmp(~lhs);
  return ExprUnary<M1>(tmp += rhs);
}

template<typename M1, typename M2>
inline auto
operator+(const M1 lhs, const Matrix<M2> &rhs)
-> enable_if_scalar_t<M1, const ExprUnary<M2>> {
  M2 tmp(~rhs);
  return ExprUnary<M2>(tmp += lhs);
}

} // Math
} // Controls

#endif // SYMCTRL_MATH_MATRIX_EXPRESSION_ADD_HPP
