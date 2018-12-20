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

  v = {3, 4};

  REQUIRE(v[0] == 3);
  REQUIRE(v[1] == 4);

  Controls::Math::Vector<int> w({1, 2});

  v = w;

  REQUIRE(v[0] == 1);
  REQUIRE(v[1] == 2);

  v[0] = 2;

  REQUIRE(w[0] == 1);

  // Addition
  v = v + w;

  REQUIRE(v[0] == 3);
  REQUIRE(v[1] == 4);

  v = w + w + w + w;

  REQUIRE(v[0] == 4);
  REQUIRE(v[1] == 8);
}

TEST_CASE("Matrix: Vector RCP<const Basic>", "[matrix]") {
  Controls::Math::Vector<RCP<const Basic>> v(2);

  REQUIRE(v.nrows() == 2);
  REQUIRE(v.ncols() == 1);

  v[0] = integer(1);
  v[1] = integer(2);

  REQUIRE(eq(*v[0], *integer(1)));
  REQUIRE(eq(*v[1], *integer(2)));

  v(0) = integer(3);
  v(1) = integer(4);

  REQUIRE(eq(*v(0), *integer(3)));
  REQUIRE(eq(*v(1), *integer(4)));

  // Transposition
  v.transpose();

  REQUIRE(v.nrows() == 1);
  REQUIRE(v.ncols() == 2);
  REQUIRE(eq(*v[0], *integer(3)));
  REQUIRE(eq(*v[1], *integer(4)));

  v.transpose();

  REQUIRE(v.nrows() == 2);
  REQUIRE(v.ncols() == 1);
  REQUIRE(eq(*v[0], *integer(3)));
  REQUIRE(eq(*v[1], *integer(4)));

  // Assignment
  v = integer(5);

  REQUIRE(eq(*v[0], *integer(5)));
  REQUIRE(eq(*v[1], *integer(5)));

  Controls::Math::Vector<RCP<const Basic>> w(2);

  w[0] = integer(1);
  w[1] = integer(2);

  v = w;

  REQUIRE(eq(*v[0], *integer(1)));
  REQUIRE(eq(*v[1], *integer(2)));

  v[0] = integer(2);

  REQUIRE(eq(*w[0], *integer(1)));

  // Addition
  v = v + w;

  REQUIRE(eq(*v[0], *integer(3)));
  REQUIRE(eq(*v[1], *integer(4)));

  v = w + w + w + w;

  REQUIRE(eq(*v[0], *integer(4)));
  REQUIRE(eq(*v[1], *integer(8)));
}

TEST_CASE("Matrix: DenseMatrix", "[matrix]") {
  Controls::Math::DenseMatrix<int> M(2, 2);

  REQUIRE(M.nrows() == 2);
  REQUIRE(M.ncols() == 2);

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

  M = Q + Q + Q + Q;

  REQUIRE(M(0, 0) == 4);
  REQUIRE(M(0, 1) == 8);
  REQUIRE(M(1, 0) == 12);
  REQUIRE(M(1, 1) == 16);

  M += 1;

  REQUIRE(M(0, 0) == 5);
  REQUIRE(M(0, 1) == 9);
  REQUIRE(M(1, 0) == 13);
  REQUIRE(M(1, 1) == 17);

  // Multiplication
  M = M * Q;

  REQUIRE(M(0, 0) == 32);
  REQUIRE(M(0, 1) == 46);
  REQUIRE(M(1, 0) == 64);
  REQUIRE(M(1, 1) == 94);

  M = Q * Q * Q * Q;

  REQUIRE(M(0, 0) == 199);
  REQUIRE(M(0, 1) == 290);
  REQUIRE(M(1, 0) == 435);
  REQUIRE(M(1, 1) == 634);

  M = Q + Q * Q + Q;

  REQUIRE(M(0, 0) == 9);
  REQUIRE(M(0, 1) == 14);
  REQUIRE(M(1, 0) == 21);
  REQUIRE(M(1, 1) == 30);

  M = Q + (Q * Q) + Q;

  REQUIRE(M(0, 0) == 9);
  REQUIRE(M(0, 1) == 14);
  REQUIRE(M(1, 0) == 21);
  REQUIRE(M(1, 1) == 30);

  Controls::Math::DenseMatrix<int> R(2, 3, {1, 2, 3, 4, 5, 6});

  M = Q * R;

  REQUIRE(M(0, 0) == 9);
  REQUIRE(M(0, 1) == 12);
  REQUIRE(M(0, 2) == 15);
  REQUIRE(M(1, 0) == 19);
  REQUIRE(M(1, 1) == 26);
  REQUIRE(M(1, 2) == 33);
}

TEST_CASE("Matrix: DenseMatrix RCP<const Basic>", "[matrix]") {
  Controls::Math::DenseMatrix<RCP<const Basic>> M(2, 2);

  M(0, 0) = integer(1);
  M(0, 1) = integer(2);
  M(1, 0) = integer(3);
  M(1, 1) = integer(4);

  REQUIRE(eq(*M(0, 0), *integer(1)));
  REQUIRE(eq(*M(0, 1), *integer(2)));
  REQUIRE(eq(*M(1, 0), *integer(3)));
  REQUIRE(eq(*M(1, 1), *integer(4)));

  // Assignment
  M = integer(5);

  REQUIRE(eq(*M(0, 0), *integer(5)));
  REQUIRE(eq(*M(0, 1), *integer(5)));
  REQUIRE(eq(*M(1, 0), *integer(5)));
  REQUIRE(eq(*M(1, 1), *integer(5)));

  Controls::Math::DenseMatrix<RCP<const Basic>> Q(2, 2);

  Q(0, 0) = integer(1);
  Q(0, 1) = integer(2);
  Q(1, 0) = integer(3);
  Q(1, 1) = integer(4);

  M = Q;

  REQUIRE(eq(*M(0, 0), *integer(1)));
  REQUIRE(eq(*M(0, 1), *integer(2)));
  REQUIRE(eq(*M(1, 0), *integer(3)));
  REQUIRE(eq(*M(1, 1), *integer(4)));

  M(0, 0) = integer(2);

  REQUIRE(eq(*Q(0, 0), *integer(1)));

  // Addition
  M = M + Q;

  REQUIRE(eq(*M(0, 0), *integer(3)));
  REQUIRE(eq(*M(0, 1), *integer(4)));
  REQUIRE(eq(*M(1, 0), *integer(6)));
  REQUIRE(eq(*M(1, 1), *integer(8)));

  M = Q + Q + Q + Q;

  REQUIRE(eq(*M(0, 0), *integer(4)));
  REQUIRE(eq(*M(0, 1), *integer(8)));
  REQUIRE(eq(*M(1, 0), *integer(12)));
  REQUIRE(eq(*M(1, 1), *integer(16)));
}
