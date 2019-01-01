#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <type_traits>

#include <symctrl/math/functor/functor.hpp>
#include <symctrl/math/functor/lambda.hpp>
// #include <symctrl/cost_function.hpp>
// #include <symctrl/transition_function.hpp>

TEST_CASE("Functor: Lambda", "[functor]") {
  {
    auto f = Controls::Math::make_lambda(
      [](const double i, const double j) -> double {
        return i*2 + j;
      }
    );

    REQUIRE(f(1, 2) == 4);
  }

  {
    double result;
    auto f = Controls::Math::make_lambda(
      [&](const double i, const double j) {
        result = i*2 + j;
      }
    );

    f(1, 2);
    REQUIRE(result == 4);
  }

  {
    double coeff = 2;
    auto f = Controls::Math::make_lambda(
      [=](const double i, const double j) -> double {
        return i*coeff + j;
      }
    );

    REQUIRE(f(1, 2) == 4);
  }
}

// TEST_CASE("Functor: Cost Function", "[function]") {
//   std::vector<double> a = {1, 2};
//   std::vector<double> b = {1, 2};
//   double c = 0;
//
//   auto f = Controls::make_cost_function(
//     [](const std::vector<double> &state,
//        const std::vector<double> &input,
//        double &result) {
//     // Perform some operation.
//     for(size_t i = 0; i < 2; i++) {
//       result += state[i] + input[i];
//     }
//   });
//
//   f->eval(a, b, c);
//
//   REQUIRE(c == 6);
//   REQUIRE(is_a_cost_function(*f));
//
//   double dummy;
//   auto g = Controls::make_lambda(
//     [](double dummy) {
//       dummy = 0;
//     }, dummy
//   );
//
//   REQUIRE(not is_a_cost_function(*g));
//
//   auto h = new Controls::DiscreteCostFunction(1, 1);
//
//   REQUIRE(is_a_cost_function(*h));
// }
//
// TEST_CASE("Functor: Transition Function", "[function]") {
//   std::vector<double> a = {1, 2};
//   std::vector<double> b = {1, 2};
//   std::vector<double> c(2);
//
//   auto f = Controls::make_transition_function(
//     [](const std::vector<double> &state,
//        const std::vector<double> &input,
//        std::vector<double> &result) {
//     // Perform some operation.
//     for(size_t i = 0; i < 2; i++) {
//       result[i] = state[i] + input[i];
//     }
//   });
//
//   f->eval(a, b, c);
//
//   REQUIRE(c[0] == 2);
//   REQUIRE(c[1] == 4);
//   REQUIRE(is_a_transition_function(*f));
//
//   double dummy;
//   auto g = Controls::make_lambda(
//     [](double dummy) {
//       dummy = 0;
//     }, dummy
//   );
//
//   REQUIRE(not is_a_transition_function(*g));
//
//   auto h = new Controls::DiscreteTransitionFunction(1, 1);
//
//   REQUIRE(is_a_transition_function(*h));
// }
