#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symctrl/math/symbolic.hpp>

using Controls::Math::BaseSymbolic;
using Controls::Math::Number;
using Controls::Math::sym_t;
using Controls::Math::Symbolic;
using Controls::Math::Variable;

// Uncomment this line to enable debugging.
#define TEST_DEBUG_OUT

#ifdef TEST_DEBUG_OUT
#define TEST_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define TEST_DEBUG(msg) // msg
#endif

TEST_CASE("Symbolic: Assignment", "[symbolic]") {
  Variable x("x");

  {
    // BaseSymbolic *y = &x;

    REQUIRE(x == Variable("x"));
    // REQUIRE(*y == Variable("x"));
  }
}

TEST_CASE("Symbolic: Addition", "[symbolic]") {
  Variable x("x");
  Variable y("y");

  auto expr = x + y;
  // decltype(expr)::show;
  // y = 1 + x;

  {
    TEST_DEBUG("*z = &x");
    BaseSymbolic* z = &x;
    // z = x;
    // REQUIRE(x == Number<int>(3));
  }

  {
    TEST_DEBUG("z = x");
    sym_t z = x;
    // REQUIRE(x == Number<int>(3));
  }

  // {
  //   sym_t z;
  //   TEST_DEBUG("z = x + y");
  //   z = x + y;
  //   // REQUIRE(x == Number<int>(3));
  // }
}
// TEST_CASE("Symbolic: Parse", "[statespace]") {
//   symbolic_symbol_t x1 = symbol("x1");
//   symbolic_symbol_t x2 = symbol("x2");
//
//   REQUIRE(equal(x1, parse("x1")));
//   REQUIRE(equal(x2, parse("x2")));
// }
//
// TEST_CASE("Symbolic: Operators", "[symbolic]") {
//   symbolic_symbol_t x = symbol("x");
//   // symbolic_t expr = 1 + 2*x + 2*x^2 + 2*x^3;
//
//   {
//     symbolic_t expr = 1 + x;
//     REQUIRE(equal(expr, parse("1 + x")));
//   }
// }
//
// TEST_CASE("Symbolic: Coefficients", "[symbolic]") {
//   symbolic_t expr = parse("1 + 2*x + 2*x^2 + 2*x3");
// }
