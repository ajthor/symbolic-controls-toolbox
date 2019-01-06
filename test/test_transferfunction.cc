#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/basic.h>
#include <symengine/symbol.h>

#include <symctrl/systems/transferfunction.hpp>
#include <symctrl/shims/equal.hpp>
#include <symctrl/shims/symbolic.hpp>
#include <symctrl/shims/parse.hpp>

using Controls::equal;
using Controls::TransferFunction;
using Controls::parse;
using Controls::symbolic_t;
using Controls::symbolic_symbol_t;

using SymEngine::symbol;

TEST_CASE("TransferFunction: Assignment", "[transferfunction]") {
  symbolic_symbol_t s = symbol("s");

  Controls::TransferFunction tf(s);

  REQUIRE(equal(tf.var(), s));

  tf.numerator =   {parse("1"), parse("1 + s")};
  tf.denominator = {parse("s"), parse("1 + s^2")};

  REQUIRE(equal(tf.numerator[0], parse("1")));
  REQUIRE(equal(tf.numerator[1], parse("1 + s")));

  REQUIRE(equal(tf.denominator[0], parse("s")));
  REQUIRE(equal(tf.denominator[1], parse("1 + s^2")));
}
