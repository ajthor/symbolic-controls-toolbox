#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <chrono>

#include <symengine/add.h>
#include <symengine/mul.h>
#include <symengine/basic.h>
#include <symengine/integer.h>
#include <symengine/symbol.h>

#include <symctrl/math/math.hpp>

using Controls::Math::DenseMatrix;
using Controls::Math::SymbolicDense;
using Controls::Math::Vector;
using Controls::Math::SymbolicVector;

using Controls::Math::StaticDense;
using Controls::Math::StaticVector;

using Controls::Math::is_lower;
using Controls::Math::is_square;
using Controls::Math::is_upper;

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

TEST_CASE("Static: Assignment", "[static]") {
  {
    StaticDense<int, 2, 2> A({0, 1, 2, 3});
    REQUIRE(A == DenseMatrix<int>(2, 2, {0, 1, 2, 3}));
  }

  {
    DenseMatrix<int> A(2, 2, {0, 1, 2, 3});
    REQUIRE(A == StaticDense<int, 2, 2>({0, 1, 2, 3}));
  }

  {
    StaticVector<int, 2, 1> A({1, 2});
    REQUIRE(A == Vector<int>({1, 2}));
  }

  {
    Vector<int> A({1, 2});
    REQUIRE(A == StaticVector<int, 2, 1>({1, 2}));
  }

  {
    DenseMatrix<int> A(2, 2, {0, 1, 2, 3});
    StaticDense<int, 2, 2> R = A;

    REQUIRE(R == A);
  }

  {
    StaticDense<int, 2, 2> A({0, 1, 2, 3});
    DenseMatrix<int> R = A;

    REQUIRE(R == A);
  }

  {
    Vector<int> A({1, 2});
    StaticVector<int, 2, 1> R = A;

    REQUIRE(R == A);
  }

  {
    StaticVector<int, 2, 1> A({1, 2});
    Vector<int> R = A;

    REQUIRE(R == A);
  }
}

TEST_CASE("Static: Add", "[static]") {
  StaticDense<int, 2, 2> A({1, 1, 1, 1});
  StaticDense<int, 2, 2> B({2, 2, 2, 2});

  {
    StaticDense<int, 2, 2> R;
    TEST_DEBUG("R = A + B");
    R = A + B;
    REQUIRE(R[0] == 3);
    REQUIRE(R[1] == 3);
    REQUIRE(R[2] == 3);
    REQUIRE(R[3] == 3);
  }
}

TEST_CASE("Static: Mul", "[static]") {
  StaticDense<int, 2, 2> A({1, 1, 1, 1});
  StaticDense<int, 2, 2> B({2, 2, 2, 2});

  {
    StaticDense<int, 2, 2> R;
    TEST_DEBUG("R = A * B");
    R = A * B;
    REQUIRE(R[0] == 4);
    REQUIRE(R[1] == 4);
    REQUIRE(R[2] == 4);
    REQUIRE(R[3] == 4);
  }

  {
    StaticDense<int, 2, 3> C({1, 2, 3, 4, 5, 6});
    StaticDense<int, 3, 2> D({1, 2, 3, 4, 5, 6});
    StaticDense<int, 2, 2> R;
    TEST_DEBUG("R = C * D");
    R = C * D;
    REQUIRE(R[0] == 22);
    REQUIRE(R[1] == 28);
    REQUIRE(R[2] == 49);
    REQUIRE(R[3] == 64);
  }
}
