#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/add.h>
#include <symengine/mul.h>
#include <symengine/basic.h>
#include <symengine/integer.h>
#include <symengine/symbol.h>

#include <math/math.hpp>

using Controls::Math::DenseMatrix;
using Controls::Math::SymbolicDense;
using Controls::Math::Vector;
using Controls::Math::SymbolicVector;

using Controls::Math::ConstantMatrix;
using Controls::Math::Identity;
using Controls::Math::Ones;
using Controls::Math::Zeros;

using SymEngine::add;
using SymEngine::Basic;
using SymEngine::integer;
using SymEngine::Integer;
using SymEngine::RCP;
using SymEngine::symbol;
using SymEngine::Symbol;

// Uncomment this line to enable debugging.
// #define TEST_DEBUG_OUT

#ifdef TEST_DEBUG_OUT
#define TEST_DEBUG(msg) \
std::cout << msg << '\n';
#else
#define TEST_DEBUG(msg) // msg
#endif

TEST_CASE("Constant: Assignment", "[dense]") {
  ConstantMatrix<int, 2, 2> C(1);
  Identity<int, 2, 2> I;
  Ones<int, 2, 2> ones;
  Zeros<int, 2, 2> zeros;

  {
    DenseMatrix<int> R(2, 2);
    R = C.as_dense();

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 1, 1, 1}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = I.as_dense();

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 0, 0, 1}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = ones.as_dense();

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 1, 1, 1}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = zeros.as_dense();

    REQUIRE(R == DenseMatrix<int>(2, 2, {0, 0, 0, 0}));
  }

  // std::cout << I[0] << '\n';
  // std::cout << I[1] << '\n';
  // std::cout << I[2] << '\n';
  // std::cout << I[3] << '\n';

  // DenseMatrix<int> C(2, 2);
  //
  // std::vector<int> v1 = {1, 2};
  // REQUIRE(A.row(0) == v1);
  //
  // std::vector<int> v2 = {3, 4};
  // REQUIRE(A.row(1) == v2);
  //
  // std::vector<int> v3 = {1, 3};
  // REQUIRE(A.col(0) == v3);
  //
  // std::vector<int> v4 = {2, 4};
  // REQUIRE(A.col(1) == v4);
  //
  // // Assignment
  // C = 5;
  //
  // REQUIRE(C(0, 0) == 5);
  // REQUIRE(C(0, 1) == 5);
  // REQUIRE(C(1, 0) == 5);
  // REQUIRE(C(1, 1) == 5);
  //
  // C = A;
  //
  // REQUIRE(C == A);
  //
  // C(0, 0) = 2;
  //
  // REQUIRE(C != A);
}

TEST_CASE("Constant: Add", "[static]") {
  Identity<int, 2, 2> I;
  Ones<int, 2, 2> ones;
  Zeros<int, 2, 2> zeros;
  DenseMatrix<int> A(2, 2, {0, 1, 2, 3});

  {
    DenseMatrix<int> R(2, 2);
    R = I + I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 0, 0, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A + I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 1, 2, 4}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = I + A;

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 1, 2, 4}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 + I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {3, 2, 2, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = I + 2;

    REQUIRE(R == DenseMatrix<int>(2, 2, {3, 2, 2, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 + zeros;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 2, 2, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = zeros + 2;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 2, 2, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A + zeros;

    REQUIRE(R == A);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = zeros + A;

    REQUIRE(R == A);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 + ones;

    REQUIRE(R == DenseMatrix<int>(2, 2, {3, 3, 3, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = ones + 2;

    REQUIRE(R == DenseMatrix<int>(2, 2, {3, 3, 3, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A + ones;

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 2, 3, 4}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = ones + A;

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 2, 3, 4}));
  }
}

TEST_CASE("Constant: Mul", "[static]") {
  Identity<int, 2, 2> I;
  Ones<int, 2, 2> ones;
  Zeros<int, 2, 2> zeros;
  DenseMatrix<int> A(2, 2, {0, 1, 2, 3});

  {
    DenseMatrix<int> R(2, 2);
    R = I * I;

    REQUIRE(R == I);
    REQUIRE(I == R);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A * I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {0, 1, 2, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = I * A;

    REQUIRE(R == DenseMatrix<int>(2, 2, {0, 1, 2, 3}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 * I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 0, 0, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = I * 2;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 0, 0, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A * 2 * I;

    REQUIRE(R == DenseMatrix<int>(2, 2, {0, 2, 4, 6}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 * I * A;

    REQUIRE(R == DenseMatrix<int>(2, 2, {0, 2, 4, 6}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 * zeros;

    REQUIRE(R == zeros);
    REQUIRE(zeros == R);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = zeros * 2;

    REQUIRE(R == zeros);
    REQUIRE(zeros == R);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A * zeros;

    REQUIRE(R == zeros);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = zeros * A;

    REQUIRE(R == zeros);
  }

  {
    DenseMatrix<int> R(2, 2);
    R = 2 * ones;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 2, 2, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = ones * 2;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 2, 2, 2}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = A * ones;

    REQUIRE(R == DenseMatrix<int>(2, 2, {1, 1, 5, 5}));
  }

  {
    DenseMatrix<int> R(2, 2);
    R = ones * A;

    REQUIRE(R == DenseMatrix<int>(2, 2, {2, 4, 2, 4}));
  }
}
