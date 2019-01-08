#ifndef SYMCTRL_SYSTEMS_EXPRESSION_TRANSFERFUNCTION_HPP
#define SYMCTRL_SYSTEMS_EXPRESSION_TRANSFERFUNCTION_HPP

#include <symengine/basic.h>
#include <symengine/add.h>
#include <symengine/mul.h>

#include <symctrl/assert.hpp>
#include <symctrl/systems/transferfunction/transferfunction.hpp>
#include <symctrl/shims/equal.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// TransferFunction Expressions
//
inline TransferFunction&
TransferFunction::operator+=(const TransferFunction &rhs) {
  SYMCTRL_ASSERT(equal(var_, rhs.var()));
  // Parallel
  num_ = SymEngine::mul(num_, rhs.numerator());
  den_ = SymEngine::mul(den_, rhs.numerator());

  return *this;
}

inline TransferFunction&
TransferFunction::operator*=(const TransferFunction &rhs) {
  SYMCTRL_ASSERT(equal(var_, rhs.var()));
  // Series
  num_ = SymEngine::add(SymEngine::mul(num_, rhs.denominator()),
                        SymEngine::mul(den_, rhs.numerator()));
  den_ = SymEngine::mul(den_, rhs.denominator());

  return *this;
}

inline TransferFunction
operator+(const TransferFunction &lhs, const TransferFunction &rhs) {
  SYMCTRL_ASSERT(equal(lhs.var(), rhs.var()));
  // Parallel
  symbolic_t num, den;

  num = SymEngine::mul(lhs.numerator(), rhs.numerator());
  den = SymEngine::mul(lhs.denominator(), rhs.denominator());

  return TransferFunction(lhs.var(), num, den);
}

inline TransferFunction
operator*(const TransferFunction &lhs, const TransferFunction &rhs) {
  SYMCTRL_ASSERT(equal(lhs.var(), rhs.var()));
  // Series
  symbolic_t num, den;

  num = SymEngine::add(SymEngine::mul(lhs.numerator(), rhs.denominator()),
                       SymEngine::mul(lhs.denominator(), rhs.numerator()));
  den = SymEngine::mul(lhs.denominator(), rhs.denominator());

  return TransferFunction(lhs.var(), num, den);
}

} // Controls

#endif // SYMCTRL_SYSTEMS_EXPRESSION_TRANSFERFUNCTION_HPP
