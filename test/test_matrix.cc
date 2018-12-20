#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/basic.h>
#include <symengine/integer.h>

#include <math/math.hpp>

using SymEngine::Basic;
using SymEngine::integer;
using SymEngine::Integer;
using SymEngine::RCP;

TEST_CASE("Matrix: Vector", "[matrix]") {
  Controls::Math::Vector<int> v(2);

  REQUIRE(v.nrows() == 2);
  REQUIRE(v.ncols() == 1);

  v[0] = 1;
  v[1] = 2;

  REQUIRE(v[0] == 1);
  REQUIRE(v[1] == 2);

  v(0) = 3;
  v(1) = 4;

  REQUIRE(v(0) == 3);
  REQUIRE(v(1) == 4);

  // Transposition
  v.transpose();

  REQUIRE(v.nrows() == 1);
  REQUIRE(v.ncols() == 2);
  REQUIRE(v[0] == 3);
  REQUIRE(v[1] == 4);

  v.transpose();

  REQUIRE(v.nrows() == 2);
  REQUIRE(v.ncols() == 1);
  REQUIRE(v[0] == 3);
  REQUIRE(v[1] == 4);

  // Assignment
  v = 5;

  REQUIRE(v[0] == 5);
  REQUIRE(v[1] == 5);

  v = {1, 2};

  REQUIRE(v[0] == 1);
  REQUIRE(v[1] == 2);

  Controls::Math::Vector<int> w({3, 4});
  v = w;

  REQUIRE(v[0] == 3);
  REQUIRE(v[1] == 4);

  v[0] = 2;

  REQUIRE(w[0] == 3);

  // Addition
  v = v + w;

  REQUIRE(v[0] == 5);
  REQUIRE(v[1] == 8);
}

TEST_CASE("Matrix: DenseMatrix int", "[matrix]") {
  Controls::Math::DenseMatrix<int> M(2, 2);

  REQUIRE(M.nrows() == 2);
  REQUIRE(M.ncols() == 2);

  // [ 1, 2 ]
  // [ 3, 4 ]
  M(0, 0) = 1;
  M(0, 1) = 2;
  M(1, 0) = 3;
  M(1, 1) = 4;

  REQUIRE(M(0, 0) == 1);
  REQUIRE(M(0, 1) == 2);
  REQUIRE(M(1, 0) == 3);
  REQUIRE(M(1, 1) == 4);

  // Controls::Math::DenseMatrix<int> Mt = M.transpose();
  //
  // REQUIRE(Mt.nrows() == 2);
  // REQUIRE(Mt.ncols() == 2);
  //
  // REQUIRE(Mt(0, 0) == 1);
  // REQUIRE(Mt(0, 1) == 3);
  // REQUIRE(Mt(1, 0) == 2);
  // REQUIRE(Mt(1, 1) == 4);

  std::vector<int> v1 = {1, 2};
  REQUIRE(M.row(0) == v1);

  std::vector<int> v2 = {3, 4};
  REQUIRE(M.row(1) == v2);

  std::vector<int> v3 = {1, 3};
  REQUIRE(M.col(0) == v3);

  std::vector<int> v4 = {2, 4};
  REQUIRE(M.col(1) == v4);

  // Assignment
  M = 5;

  REQUIRE(M(0, 0) == 5);
  REQUIRE(M(0, 1) == 5);
  REQUIRE(M(1, 0) == 5);
  REQUIRE(M(1, 1) == 5);

  Controls::Math::DenseMatrix<int> Q(2, 2, {1, 2, 3, 4});

  M = Q;

  REQUIRE(M(0, 0) == 1);
  REQUIRE(M(0, 1) == 2);
  REQUIRE(M(1, 0) == 3);
  REQUIRE(M(1, 1) == 4);

  M(0, 0) = 2;

  REQUIRE(Q(0, 0) == 1);

  // Addition
  M = M + Q;

  REQUIRE(M(0, 0) == 3);
  REQUIRE(M(0, 1) == 4);
  REQUIRE(M(1, 0) == 6);
  REQUIRE(M(1, 1) == 8);

  M += 1;

  REQUIRE(M(0, 0) == 4);
  REQUIRE(M(0, 1) == 5);
  REQUIRE(M(1, 0) == 7);
  REQUIRE(M(1, 1) == 9);
}

TEST_CASE("Matrix: DenseMatrix RCP<const Integer>", "[matrix]") {
  Controls::Math::DenseMatrix<RCP<const Integer>> M(2, 2);

  M(0, 0) = integer(1);
  M(0, 1) = integer(2);
  M(1, 0) = integer(3);
  M(1, 1) = integer(4);

  REQUIRE(eq(*M(0, 0), *integer(1)));
  REQUIRE(eq(*M(0, 1), *integer(2)));
  REQUIRE(eq(*M(1, 0), *integer(3)));
  REQUIRE(eq(*M(1, 1), *integer(4)));
}
