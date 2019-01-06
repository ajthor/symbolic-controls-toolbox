#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/visitor.h>
#include <symengine/parser.h>

#include <symctrl/math/random/random_variable.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/systems/statespace.hpp>
#include <symctrl/systems/visitor.hpp>
#include <symctrl/systems/visitors/subs.hpp>
#include <symctrl/shims/equal.hpp>
#include <symctrl/shims/symbolic.hpp>
#include <symctrl/shims/parse.hpp>

using Controls::equal;
using Controls::linearize;
using Controls::Math::SymbolicDense;
using Controls::parse;
using Controls::StateSpace;
using Controls::symbolic_t;
using Controls::symbolic_symbol_t;

using SymEngine::Basic;
using SymEngine::RCP;
using SymEngine::symbol;
using SymEngine::Symbol;

TEST_CASE("StateSpace: Parse", "[statespace]") {
  symbolic_symbol_t x1 = symbol("x1");
  symbolic_symbol_t x2 = symbol("x2");

  REQUIRE(equal(x1, parse("x1")));
  REQUIRE(equal(x2, parse("x2")));
}

TEST_CASE("StateSpace: Assignment", "[statespace]") {
  symbolic_symbol_t x1 = symbol("x1");
  symbolic_symbol_t x2 = symbol("x2");
  symbolic_symbol_t u = symbol("u");

  StateSpace sys;

  sys.state_variables = {x1, x2};
  sys.input_variables = {u};
  sys.state_equations = {parse("x2"), parse("-sin(x1) - x2")};
  sys.output_equations = {parse("x1"), parse("x2")};

  REQUIRE(equal(sys.state_variables[0], x1));
  REQUIRE(equal(sys.state_variables[1], x2));
  REQUIRE(sys.state_variables.size() == 2);

  REQUIRE(equal(sys.input_variables[0], u));
  REQUIRE(sys.input_variables.size() == 1);

  REQUIRE(equal(sys.state_equations[0], parse("x2")));
  REQUIRE(equal(sys.state_equations[1], parse("-sin(x1) - x2")));
  REQUIRE(sys.state_equations.size() == 2);

  REQUIRE(equal(sys.output_equations[0], parse("x1")));
  REQUIRE(equal(sys.output_equations[1], parse("x2")));
  REQUIRE(sys.output_equations.size() == 2);
}

TEST_CASE("StateSpace: ABCD Matrices", "[statespace]") {
  StateSpace sys;

  sys.state_variables = {parse("x1"), parse("x2")};
  sys.input_variables = {parse("u")};
  sys.state_equations = {parse("x2"), parse("-sin(x1) - x2 + u")};
  sys.output_equations = {parse("x1"), parse("x2")};

  SymbolicDense A = state_matrix(sys);
  SymbolicDense B = input_matrix(sys);
  SymbolicDense C = output_matrix(sys);
  SymbolicDense D = feedforward_matrix(sys);

  REQUIRE(A == SymbolicDense(2, 2, {parse("0"),         parse("1"),
                                    parse("-cos(x1)"),  parse("-1")}));

  REQUIRE(B == SymbolicDense(2, 1, {parse("0"),
                                    parse("1")}));

  REQUIRE(C == SymbolicDense(2, 2, {parse("1"),         parse("0"),
                                    parse("0"),         parse("1")}));

  REQUIRE(D == SymbolicDense(2, 1, {parse("0"),
                                    parse("0")}));

  SymbolicDense AA = Controls::A_matrix(sys);
  SymbolicDense BB = Controls::B_matrix(sys);
  SymbolicDense CC = Controls::C_matrix(sys);
  SymbolicDense DD = Controls::D_matrix(sys);

  REQUIRE(A == AA);
  REQUIRE(B == BB);
  REQUIRE(C == CC);
  REQUIRE(D == DD);

  SymbolicDense AAA = sys.A();
  SymbolicDense BBB = sys.B();
  SymbolicDense CCC = sys.C();
  SymbolicDense DDD = sys.D();

  REQUIRE(A == AAA);
  REQUIRE(B == BBB);
  REQUIRE(C == CCC);
  REQUIRE(D == DDD);
}

// TEST_CASE("State space: nonlinear separation", "[statespace]") {
//   Controls::StateSpace *ss = new Controls::StateSpace();
//
//   RCP<const Symbol> x = symbol("x");
//   RCP<const Symbol> u = symbol("u");
//   RCP<const Symbol> a = symbol("a");
//   RCP<const Symbol> b = symbol("b");
//
//   ss->add_state(x);
//   ss->add_input(u);
//
//   std::string s;
//   RCP<const Basic> res, V;
//
//   s = "a*x - b*x^3 + u";
//   res = SymEngine::parse(s);
//   ss->add_f(res);
//
//   s = "x^2/2";
//   V = SymEngine::parse(s);
//
// }

TEST_CASE("StateSpace: Random Variable", "[statespace]") {
  symbolic_symbol_t x1 = symbol("x1");
  symbolic_symbol_t x2 = symbol("x2");
  symbolic_symbol_t u = symbol("u");

  Controls::Math::normal_distribution<> d1{0, 1};
  Controls::Math::normal_distribution<> d2{0, 1};

  RCP<const Controls::Math::RandomVariable> w1;
  RCP<const Controls::Math::RandomVariable> w2;
  w1 = Controls::Math::random_variable("w1", &d1);
  w2 = Controls::Math::random_variable("w2", &d2);

  StateSpace sys;

  sys.state_variables = {x1, x2};
  sys.input_variables = {u};
  sys.state_equations = {parse("x2 + w1"), parse("-sin(x1) - x2 + u + w2")};
  sys.output_equations = {parse("x1"), parse("x2")};

  REQUIRE(equal(sys.state_equations[0], parse("x2 + w1")));
  REQUIRE(equal(sys.state_equations[1], parse("-sin(x1) - x2 + u + w2")));
}

TEST_CASE("StateSpace: Subs", "[statespace]") {
  StateSpace sys({parse("x1"), parse("x2")},
                 {parse("u")},
                 {parse("x2"), parse("-sin(x1) - x2 + u")},
                 {parse("x1"), parse("x2")});
  //
  symbolic_symbol_t x3 = symbol("x3");

  subs(sys, parse("x1"), x3);

  SymbolicDense A = state_matrix(sys);

  REQUIRE(equal(sys.state_variables[0], x3));
  REQUIRE(A == SymbolicDense(2, 2, {parse("0"),         parse("1"),
                                    parse("-cos(x3)"),  parse("-1")}));


}
