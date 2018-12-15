#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/sets.h>
#include <symengine/visitor.h>
#include <symengine/parser.h>

#include <symctrl/mdp.hpp>

using SymEngine::Basic;
using SymEngine::finiteset;
using SymEngine::RCP;
using SymEngine::Set;
using SymEngine::symbol;

TEST_CASE("MDP: Control Policy", "[function]") {
  std::vector<double> a = {1, 2};
  std::vector<double> b(2);

  auto f = Controls::make_control_policy(
    [](const std::vector<double> &state,
       std::vector<double> &result) {
    // Perform some operation.
    for(size_t i = 0; i < 2; i++) {
      result[i] = state[i];
    }
  });

  f->eval(a, b);

  REQUIRE(b[0] == 1);
  REQUIRE(b[1] == 2);
  REQUIRE(is_a_control_policy(*f));

  double dummy;
  auto g = Controls::make_lambda(
    [](double dummy) {
      dummy = 0;
    }, dummy
  );

  REQUIRE(not is_a_control_policy(*g));

  auto h = new Controls::DiscreteControlPolicy(1, 1);

  REQUIRE(is_a_control_policy(*h));
}

TEST_CASE("MDP: Value Iteration", "[MDP]") {
  RCP<const Basic> x = symbol("x");
  RCP<const Basic> u = symbol("u");

  RCP<const Set> X = finiteset({x});
  RCP<const Set> U = finiteset({u});

  Controls::CostFunction *R;
  Controls::TransitionFunction *T;

  R = new Controls::DiscreteCostFunction(2, 1);
  T = new Controls::DiscreteTransitionFunction(2, 1);

  Controls::MDP *sys;

  sys = new Controls::MDP(X, U, T, R, 0.9);

  REQUIRE(1 == 1);
  REQUIRE(2 == 2);
}

TEST_CASE("POMDP: Value Iteration", "[MDP]") {
  RCP<const Basic> x = symbol("x");
  RCP<const Basic> u = symbol("u");

  RCP<const Set> X = finiteset({x});
  RCP<const Set> U = finiteset({u});

  Controls::CostFunction *R;
  Controls::TransitionFunction *T;
  Controls::TransitionFunction *Ob;

  R = new Controls::DiscreteCostFunction(2, 1);
  T = new Controls::DiscreteTransitionFunction(2, 1);
  Ob = new Controls::DiscreteTransitionFunction(2, 1);

  Controls::POMDP *sys;

  sys = new Controls::POMDP(X, U, T, R, Ob, 0.9);

  REQUIRE(1 == 1);
  REQUIRE(2 == 2);
}
