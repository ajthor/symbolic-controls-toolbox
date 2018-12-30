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

TEST_CASE("Vector: Assignment", "[vector]") {
  Vector<int> a({1, 1});
  Vector<int> r(2);

  // Assignment
  r = 5;

  REQUIRE(r[0] == 5);
  REQUIRE(r[1] == 5);

  r = a;

  REQUIRE(r == a);

  r[0] = 2;

  REQUIRE(r != a);
}

TEST_CASE("Vector: Add", "[vector]") {
  Vector<int> a({1, 1});
  Vector<int> b({2, 2});

  {
    Vector<int> r(2);
    TEST_DEBUG("r = a + b");
    r = a + b;
    REQUIRE(r[0] == 3);
    REQUIRE(r[1] == 3);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = 5 + a");
    r = 5 + a;
    REQUIRE(r[0] == 6);
    REQUIRE(r[1] == 6);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = a + 5");
    r = a + 5;
    REQUIRE(r[0] == 6);
    REQUIRE(r[1] == 6);
  }
}

TEST_CASE("Vector: Mul", "[vector]") {
  Vector<int> a({1, 1});
  Vector<int> b({2, 2});

  // {
  //   Vector<int> r(2);
  //   TEST_DEBUG("r = a * b");
  //   r = a * b;
  //   REQUIRE(r[0] = 3);
  //   REQUIRE(r[1] = 3);
  // }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = 5 * a");
    r = 5 * a;
    REQUIRE(r[0] == 5);
    REQUIRE(r[1] == 5);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = a * 5");
    r = a * 5;
    REQUIRE(r[0] == 5);
    REQUIRE(r[1] == 5);
  }
}

TEST_CASE("Vector: Add/Mul", "[vector]") {
  Vector<int> a({1, 1});
  Vector<int> b({2, 2});
  Vector<int> c({3, 3});

  {
    Vector<int> r(2);
    TEST_DEBUG("r = a + (b + c)");
    r = a + (b + c);
    REQUIRE(r[0] == 6);
    REQUIRE(r[1] == 6);
  }

  // {
  //   Vector<int> r(2);
  //   TEST_DEBUG("r = a * (b + c)");
  //   r = a * (b + c);
  //   REQUIRE(r[0] == 6);
  //   REQUIRE(r[1] == 6);
  // }

  // {
  //   Vector<int> r(2);
  //   TEST_DEBUG("r = a + (b * c)");
  //   r = a + (b * c);
  //   REQUIRE(r[0] == 6);
  //   REQUIRE(r[1] == 6);
  // }

  // {
  //   Vector<int> r(2);
  //   TEST_DEBUG("r = a * (b * c)");
  //   r = a * (b * c);
  //   REQUIRE(r[0] == 6);
  //   REQUIRE(r[1] == 6);
  // }
}

TEST_CASE("Vector: transpose", "[vector]") {
  Vector<int> a({1, 2});
  Vector<int> b({2, 3});

  {
    Vector<int> r(2);
    TEST_DEBUG("r = transpose(a)");
    r = transpose(a);
    REQUIRE(r != a);
    REQUIRE(r.nrows() == 1);
    REQUIRE(r.ncols() == 2);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = transpose(transpose(a))");
    r = transpose(transpose(a));
    REQUIRE(r == a);
    REQUIRE(r.nrows() == 2);
    REQUIRE(r.ncols() == 1);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = transpose(a) + transpose(b)");
    r = transpose(a) + transpose(b);
    REQUIRE(r[0] == 3);
    REQUIRE(r[1] == 5);
  }

  {
    Vector<int> r(2);
    TEST_DEBUG("r = transpose(a + b)");
    r = transpose(a + b);
    REQUIRE(r[0] == 3);
    REQUIRE(r[1] == 5);
  }
}

// TEST_CASE("Vector: Mixed operations", "[vector]") {
//   DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
//   Vector<int> x({1, 1});
//
//   {
//     Vector<int> r(2);
//
//     r = A * x;
//
//     REQUIRE(r.nrows() == 2);
//     REQUIRE(r.ncols() == 1);
//
//     REQUIRE(r[0] == 2);
//     REQUIRE(r[1] == 2);
//   }
//
//   {
//     DenseMatrix<int> R(2, 1);
//
//     R = A * x;
//
//     REQUIRE(R.nrows() == 2);
//     REQUIRE(R.ncols() == 1);
//
//     REQUIRE(R[0] == 2);
//     REQUIRE(R[1] == 2);
//   }
//
//   {
//     Vector<int> r(2);
//
//     r = transpose(x) * A;
//
//     REQUIRE(r.nrows() == 1);
//     REQUIRE(r.ncols() == 2);
//
//     REQUIRE(r[0] == 2);
//     REQUIRE(r[1] == 2);
//   }
//
//   {
//     DenseMatrix<int> R(1, 2);
//
//     R = transpose(x) * A;
//
//     REQUIRE(R.nrows() == 1);
//     REQUIRE(R.ncols() == 2);
//
//     REQUIRE(R[0] == 2);
//     REQUIRE(R[1] == 2);
//   }
//
//   {
//     DenseMatrix<int> R(2, 2);
//
//     R = 2 * A;
//
//     REQUIRE(R[0] == 2);
//     REQUIRE(R[1] == 2);
//     REQUIRE(R[2] == 2);
//     REQUIRE(R[3] == 2);
//   }
//
//   {
//     DenseMatrix<int> R(2, 2);
//
//     R = A * 2;
//
//     REQUIRE(R[0] == 2);
//     REQUIRE(R[1] == 2);
//     REQUIRE(R[2] == 2);
//     REQUIRE(R[3] == 2);
//   }
//
//   {
//     SymbolicDense C(2, 2);
//     SymbolicDense D(2, 2, {integer(1), integer(0), integer(0), integer(1)});
//     RCP<const Basic> x = symbol("x");
//
//     C = x * D;
//
//     REQUIRE(eq(*C[0], *x));
//     REQUIRE(eq(*C[1], *integer(0)));
//     REQUIRE(eq(*C[2], *integer(0)));
//     REQUIRE(eq(*C[3], *x));
//   }
//
// }
//
// TEST_CASE("Vector: Vector RCP<const Basic>", "[vector]") {
//   Vector<RCP<const Basic>> a({integer(1), integer(1)});
//   Vector<RCP<const Basic>> r(2);
//
//   // Assignment
//   r = integer(5);
//
//   REQUIRE(eq(*r[0], *integer(5)));
//   REQUIRE(eq(*r[1], *integer(5)));
//
//   r = a;
//
//   REQUIRE(r == a);
//
//   r[0] = integer(2);
//
//   REQUIRE(r != a);
//
//   // // Addition
//   // v = v + w;
//   //
//   // REQUIRE(eq(*v[0], *integer(3)));
//   // REQUIRE(eq(*v[1], *integer(4)));
//   //
//   // v = w + w + w + w;
//   //
//   // REQUIRE(eq(*v[0], *integer(4)));
//   // REQUIRE(eq(*v[1], *integer(8)));
// }

TEST_CASE("Vector: Norm", "[vector]") {
  Vector<int> v({1, -2, 3});

  {
    auto result = Controls::Math::norm(v, 1);
    REQUIRE(::fabs(result - 6) < 1e-3);
  }

  {
    auto result = Controls::Math::norm(v, 2);
    REQUIRE(::fabs(result - 3.7417) < 1e-3);
  }

  {
    auto result = Controls::Math::norm(v, 3);
    REQUIRE(::fabs(result - 3.3019) < 1e-3);
  }

  {
    auto result = Controls::Math::infinity_norm(v);
    REQUIRE(result == 3);
  }
}
