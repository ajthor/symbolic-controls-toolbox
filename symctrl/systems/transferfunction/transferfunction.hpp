#ifndef SYMCTRL_SYSTEMS_TRANSFERFUNCTION_TRANSFERFUNCTION_HPP
#define SYMCTRL_SYSTEMS_TRANSFERFUNCTION_TRANSFERFUNCTION_HPP

#include <vector>

#include <symengine/basic.h>
#include <symengine/symbol.h>

#include <symctrl/systems/system.hpp>
#include <symctrl/math/matrix/vector.hpp>
#include <symctrl/shims/symbolic.hpp>

namespace Controls {

class TransferFunction : public System<TransferFunction> {
public:
  explicit inline TransferFunction();
  explicit inline TransferFunction(const symbolic_symbol_t v);

  inline TransferFunction(const TransferFunction &m);

  inline TransferFunction &operator=(const TransferFunction &rhs);

private:
  symbolic_symbol_t var_;

  // NOTE: This might be better as a matrix of n/d pairs with accessors.
  class ExpressionVector : public Math::SymbolicVector {
  public:
    using Math::SymbolicVector::SymbolicVector;
    using Math::SymbolicVector::operator=;
  };

public:
  inline symbolic_t var() const;

  // Vector of numerators.
  ExpressionVector numerator;

  // Vector of denominators.
  ExpressionVector denominator;

  inline void accept(Visitor &visitor);
};

// ----------------------------------------------------------------------
// TransferFunction Constructor
//
inline TransferFunction::TransferFunction() {
  var_ = SymEngine::symbol("s");
  numerator = ExpressionVector(0);
  denominator = ExpressionVector(0);
}
inline TransferFunction::TransferFunction(const symbolic_symbol_t v) {
  //
  var_ = v;
  numerator = ExpressionVector(0);
  denominator = ExpressionVector(0);
}

inline TransferFunction::TransferFunction(const TransferFunction &m) {
  var_ = m.var_;
  numerator = m.numerator;
  denominator = m.denominator;
}

// ----------------------------------------------------------------------
// TransferFunction Assignment Operator
//
inline TransferFunction&
TransferFunction::operator=(const TransferFunction &rhs) {
  var_ = rhs.var_;
  numerator = rhs.numerator;
  denominator = rhs.denominator;

  return *this;
}

// ----------------------------------------------------------------------
// TransferFunction Member Function Definitions
//
inline symbolic_t TransferFunction::var() const {
  return var_;
}

} // Controls

#endif // SYMCTRL_SYSTEMS_TRANSFERFUNCTION_TRANSFERFUNCTION_HPP
