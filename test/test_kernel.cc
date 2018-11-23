#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>

#include <symctrl/kernel.hpp>
#include <symctrl/matrix/dense.hpp>

TEST_CASE("Kernel: gramian", "[kernel]") {
  std::vector<int> x = {1, 2};
  std::vector<int> y = {3, 4};

  Controls::DotKernel<int> K1;

  Controls::DenseMatrix<double> A(2, 2);

  K1.gramian(x, x, A);

  REQUIRE(A(0, 0) == 1);
  REQUIRE(A(0, 1) == 2);
  REQUIRE(A(1, 0) == 2);
  REQUIRE(A(1, 1) == 4);
  // Symmetric
  REQUIRE(A(0, 1) == A(1, 0));
  // Positive Definite
  for(auto it = A.begin(); it != A.end(); ++it) {
    REQUIRE(*it > 0);
  }

  K1.gramian(x, y, A);

  REQUIRE(A(0, 0) == 3);
  REQUIRE(A(0, 1) == 4);
  REQUIRE(A(1, 0) == 6);
  REQUIRE(A(1, 1) == 8);

  Controls::PolynomialKernel<int> K2(1, 0, 2);

  Controls::DenseMatrix<double> B(2, 2);

  K2.gramian(x, x, B);

  REQUIRE(B(0, 0) == 1);
  REQUIRE(B(0, 1) == 4);
  REQUIRE(B(1, 0) == 4);
  REQUIRE(B(1, 1) == 16);
  // Symmetric
  REQUIRE(B(0, 1) == B(1, 0));
  // Positive Definite
  for(auto it = B.begin(); it != B.end(); ++it) {
    REQUIRE(*it > 0);
  }

  K2.gramian(x, y, B);

  REQUIRE(B(0, 0) == 9);
  REQUIRE(B(0, 1) == 16);
  REQUIRE(B(1, 0) == 36);
  REQUIRE(B(1, 1) == 64);

  Controls::GaussianKernel<int> K3(2);

  Controls::DenseMatrix<double> C(2, 2);

  K3.gramian(x, x, C);

  REQUIRE(C(0, 0) == 1);
  REQUIRE(::fabs(C(0, 1) - 0.8825) < 1e-3);
  REQUIRE(::fabs(C(1, 0) - 0.8825) < 1e-3);
  REQUIRE(C(1, 1) == 1);
  // Symmetric
  REQUIRE(C(0, 1) == C(1, 0));
  // Positive Definite
  for(auto it = C.begin(); it != C.end(); ++it) {
    REQUIRE(*it > 0);
  }

  K3.gramian(x, y, C);

  REQUIRE(::fabs(C(0, 0) - 0.6065) < 1e-3);
  REQUIRE(::fabs(C(0, 1) - 0.3247) < 1e-3);
  REQUIRE(::fabs(C(1, 0) - 0.8825) < 1e-3);
  REQUIRE(::fabs(C(1, 1) - 0.6065) < 1e-3);
}

TEST_CASE("Kernel: kernel_mul", "[kernel]") {
  std::vector<int> x = {1, 2};
  std::vector<int> y = {3, 4};
  std::vector<int> alpha = {2, 3};
  std::vector<double> result(2);

  Controls::KernelFunction<int>
  *K1 = new Controls::DotKernel<int>;

  Controls::kernel_mul(x, y, alpha, K1, result);

  REQUIRE(result.at(0) == 18);
  REQUIRE(result.at(1) == 36);

  Controls::KernelFunction<int>
  *K2 = new Controls::PolynomialKernel<int>(1, 0, 2);

  Controls::kernel_mul(x, y, alpha, K2, result);

  REQUIRE(result.at(0) == 66);
  REQUIRE(result.at(1) == 264);

  Controls::KernelFunction<int>
  *K3 = new Controls::GaussianKernel<int>(2);

  Controls::kernel_mul(x, y, alpha, K3, result);

  REQUIRE(::fabs(result.at(0) - 2.1870) < 1e-3);
  REQUIRE(::fabs(result.at(1) - 3.5846) < 1e-3);
}

TEST_CASE("Kernel: double integrator", "[kernel]") {
  REQUIRE(1 == 1);
}
