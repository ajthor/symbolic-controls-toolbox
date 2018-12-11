#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symctrl/matrix/dense.hpp>

TEST_CASE("Dense Matrix", "[densematrix]") {
  Controls::DenseMatrix<double> A(1, 1);
  REQUIRE(A.nrows() == 1);
  REQUIRE(A.ncols() == 1);

  A(0, 0) = 2.0;
  REQUIRE(A(0, 0) == 2.0);

  Controls::DenseMatrix<double> B(2, 2);
  REQUIRE(B.nrows() == 2);
  REQUIRE(B.ncols() == 2);

  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;
  REQUIRE(B(0, 0) == 1.0);
  REQUIRE(B(0, 1) == 2.0);
  REQUIRE(B(1, 0) == 3.0);
  REQUIRE(B(1, 1) == 4.0);

  std::vector<double> v = {1, 2, 3, 4};
  Controls::DenseMatrix<double> C(2, 2, v);
  REQUIRE(C.nrows() == 2);
  REQUIRE(C.ncols() == 2);
  REQUIRE(C(0, 0) == 1.0);
  REQUIRE(C(0, 1) == 2.0);
  REQUIRE(C(1, 0) == 3.0);
  REQUIRE(C(1, 1) == 4.0);

  Controls::DenseMatrix<double> D(2, 2, {1, 2, 3, 4});
  REQUIRE(D.nrows() == 2);
  REQUIRE(D.ncols() == 2);
  REQUIRE(D(0, 0) == 1.0);
  REQUIRE(D(0, 1) == 2.0);
  REQUIRE(D(1, 0) == 3.0);
  REQUIRE(D(1, 1) == 4.0);
}

TEST_CASE("Dense Matrix: ones", "[densematrix]") {
  Controls::DenseMatrix<double> A(2, 2);
  ones(A);
  for(auto it = A.begin(); it != A.end(); ++it) {
    REQUIRE(*it > 0);
  }

  Controls::DenseMatrix<double> B(2, 3);
  ones(B);
  for(auto it = B.begin(); it != B.end(); ++it) {
    REQUIRE(*it > 0);
  }
}

TEST_CASE("Dense Matrix: zeros", "[densematrix]") {
  Controls::DenseMatrix<double> A(2, 2);
  zeros(A);
  for(auto it = A.begin(); it != A.end(); ++it) {
    REQUIRE(*it > 0);
  }

  Controls::DenseMatrix<double> B(2, 3);
  zeros(B);
  for(auto it = B.begin(); it != B.end(); ++it) {
    REQUIRE(*it > 0);
  }
}

TEST_CASE("Dense Matrix: eye", "[densematrix]") {
  Controls::DenseMatrix<double> A(2, 2);
  eye(A);
  REQUIRE(A(0, 0) == 1);
  REQUIRE(A(0, 1) == 0);
  REQUIRE(A(1, 0) == 0);
  REQUIRE(A(1, 1) == 1);

  Controls::DenseMatrix<double> B(2, 3);
  eye(B);
  REQUIRE(B(0, 0) == 1);
  REQUIRE(B(0, 1) == 0);
  REQUIRE(B(0, 2) == 0);
  REQUIRE(B(1, 0) == 0);
  REQUIRE(B(1, 1) == 1);
  REQUIRE(B(1, 2) == 0);
}
