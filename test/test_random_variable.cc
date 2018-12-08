#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/visitor.h>
#include <symengine/parser.h>

#include <symengine/cwrapper.h>
#include <symctrl/c_wrapper.hpp>

#include <symctrl/random_variable.hpp>

using SymEngine::add;
using SymEngine::Add;
using SymEngine::Basic;
using SymEngine::RCP;

TEST_CASE("Random Variable", "[randomvariable]") {
  std::random_device rd;
  Controls::normal_distribution<> d{5,2};

  RCP<const Controls::RandomVariable> X;
  X = Controls::random_variable("X", &d);

  REQUIRE(Controls::is_a_random_variable(*X));
  REQUIRE(X->get_name() == "X");

  RCP<const Basic> y = SymEngine::symbol("y");

  REQUIRE(not Controls::is_a_random_variable(*y));

  // std::cout << d(rd) << '\n';
  // std::cout << X->sample(rd) << '\n';
}

TEST_CASE("Random Variable: add", "[randomvariable]") {
  std::random_device rd;
  Controls::normal_distribution<> d{5,2};

  RCP<const Controls::RandomVariable> X;
  X = Controls::random_variable("X", &d);

  RCP<const Basic> y = SymEngine::symbol("y");

  RCP<const Basic> r = add(add(X, y), y);

  std::string s;
  RCP<const Basic> res;

  s = "X + 2*y";
  res = SymEngine::parse(s);

  REQUIRE(res->__eq__(*r));
  REQUIRE(SymEngine::has_symbol(*r, *X));

  RCP<const Add> ar = SymEngine::rcp_static_cast<const Add>(r);
  const SymEngine::umap_basic_num &add_map = ar->get_dict();
  auto search = add_map.find(X);
  REQUIRE(search != add_map.end());
  REQUIRE(eq(*search->first, *X));
  REQUIRE(Controls::is_a_random_variable(*search->first));
}

TEST_CASE("Random Variable: Wrapper", "[randomvariable]") {
  auto d = random_number_distribution_new();
  normal_distribution_set(d, 0, 1);

  auto s = random_variable_new();
  random_variable_set(s, "x", d);

  // std::cout << *(s->m) << '\n';

  double r = random_variable_sample(s);
  // std::cout << "TEST SAMPLE" << '\n';
  // std::cout << random_variable_sample(s) << '\n';

  random_variable_free(s);
  random_number_distribution_free(d);

  // REQUIRE(0 == 1);
}
