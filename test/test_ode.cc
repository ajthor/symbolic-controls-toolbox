#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/visitor.h>
#include <symengine/parser.h>

#include <symctrl/ode/euler.hpp>

TEST_CASE("ODE: Euler", "[ODE]") {
  Controls::StateSpace *ss = new Controls::StateSpace();

  SymEngine::RCP<const SymEngine::Symbol> x = SymEngine::symbol("x");

  std::string s;
  SymEngine::RCP<const SymEngine::Basic> res;

  ss->add_state(x);

  s = "2*x + 1";
  res = SymEngine::parse(s);
  ss->add_f(res);

  std::vector<double> t_span = {0, 1};
  std::vector<double> x0 = {1};
  std::vector<double> t_result;
  std::vector<double> x_result;
  Controls::OdeOptions *options = new Controls::OdeOptions();

  Controls::ode_euler(*ss, t_span, x0, t_result, x_result, *options);

  REQUIRE(::fabs(x_result.front() - 1.0) < 1e-9);
  REQUIRE(::fabs(x_result.back() - 10.5614685855) < 1e-9);

  REQUIRE(x_result.size() == 1001);
  REQUIRE(t_result.size() == 1001);
}

TEST_CASE("ODE: Euler Pendulum", "[ODE]") {
  Controls::StateSpace *ss = new Controls::StateSpace();

  SymEngine::RCP<const SymEngine::Symbol> x1 = SymEngine::symbol("x1");
  SymEngine::RCP<const SymEngine::Symbol> x2 = SymEngine::symbol("x2");

  std::string s;
  SymEngine::RCP<const SymEngine::Basic> res;

  ss->add_state(x1);
  ss->add_state(x2);

  s = "-x2";
  res = SymEngine::parse(s);
  ss->add_f(res);

  s = "-sin(x1) - x2";
  res = SymEngine::parse(s);
  ss->add_f(res);

  std::vector<double> t_span = {0, 20};
  std::vector<double> x0 = {2, 0};
  std::vector<double> t_result;
  std::vector<double> x_result;
  Controls::OdeOptions *options = new Controls::OdeOptions();

  Controls::ode_euler(*ss, t_span, x0, t_result, x_result, *options);

  REQUIRE(::fabs(x_result.at(0) - 2.00) < 1e-3);
  REQUIRE(::fabs(x_result.at(1) - 0.00) < 1e-3);
  REQUIRE(::fabs(x_result.at(40001) - 3.141) < 1e-3);
  REQUIRE(::fabs(x_result.at(40002) - 0.000) < 1e-3);

  REQUIRE(x_result.size() == 40002);
  REQUIRE(t_result.size() == 20001);
}
