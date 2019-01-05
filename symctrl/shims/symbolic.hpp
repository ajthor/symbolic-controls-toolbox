#ifndef SYMCTRL_SHIMS_SYMBOLIC_HPP
#define SYMCTRL_SHIMS_SYMBOLIC_HPP

#include <symengine/basic.h>
#include <symengine/constants.h>
#include <symengine/integer.h>
#include <symengine/symbol.h>
#include <symengine/parser.h>

namespace Controls {

// ----------------------------------------------------------------------
// symbolic
//
struct symbolic {
  using type = SymEngine::RCP<const SymEngine::Basic>;
};

using symbolic_t = typename symbolic::type;

// ----------------------------------------------------------------------
// symbolic_integer
//
struct symbolic_integer {
  using type = SymEngine::RCP<const SymEngine::Integer>;
};

using symbolic_integer_t = typename symbolic_integer::type;

// ----------------------------------------------------------------------
// symbolic_symbol
//
struct symbolic_symbol {
  using type = SymEngine::RCP<const SymEngine::Symbol>;
};

using symbolic_symbol_t = typename symbolic_symbol::type;

// ----------------------------------------------------------------------
// symbolic_one
//
inline symbolic_t symbolic_one() {
  return SymEngine::one;
}

// ----------------------------------------------------------------------
// symbolic_zero
//
inline symbolic_t symbolic_zero() {
  return SymEngine::zero;
}

} // Controls

#endif // SYMCTRL_SHIMS_SYMBOLIC_HPP
