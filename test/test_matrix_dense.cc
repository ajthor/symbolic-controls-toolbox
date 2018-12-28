#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <symengine/add.h>
#include <symengine/mul.h>
#include <symengine/basic.h>
#include <symengine/integer.h>
#include <symengine/symbol.h>

#include <math/math.hpp>

using Controls::Math::DenseMatrix;
using Controls::Math::SymbolicMatrix;
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

TEST_CASE("Dense: Assignment", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 2, 3, 4});
  DenseMatrix<int> C(2, 2);

  std::vector<int> v1 = {1, 2};
  REQUIRE(A.row(0) == v1);

  std::vector<int> v2 = {3, 4};
  REQUIRE(A.row(1) == v2);

  std::vector<int> v3 = {1, 3};
  REQUIRE(A.col(0) == v3);

  std::vector<int> v4 = {2, 4};
  REQUIRE(A.col(1) == v4);

  // Assignment
  C = 5;

  REQUIRE(C(0, 0) == 5);
  REQUIRE(C(0, 1) == 5);
  REQUIRE(C(1, 0) == 5);
  REQUIRE(C(1, 1) == 5);

  C = A;

  REQUIRE(C == A);

  C(0, 0) = 2;

  REQUIRE(C != A);
}

TEST_CASE("Dense: Add", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
  DenseMatrix<int> B(2, 2, {2, 2, 2, 2});

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A + B");
    R = A + B;
    REQUIRE(R[0] == 3);
    REQUIRE(R[1] == 3);
    REQUIRE(R[2] == 3);
    REQUIRE(R[3] == 3);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = 5 + A");
    R = 5 + A;
    REQUIRE(R[0] == 6);
    REQUIRE(R[1] == 6);
    REQUIRE(R[2] == 6);
    REQUIRE(R[3] == 6);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A + 5");
    R = A + 5;
    REQUIRE(R[0] == 6);
    REQUIRE(R[1] == 6);
    REQUIRE(R[2] == 6);
    REQUIRE(R[3] == 6);
  }
}

TEST_CASE("Dense: Mul", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
  DenseMatrix<int> B(2, 2, {2, 2, 2, 2});

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A * B");
    R = A * B;
    REQUIRE(R[0] == 4);
    REQUIRE(R[1] == 4);
    REQUIRE(R[2] == 4);
    REQUIRE(R[3] == 4);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = 5 * A");
    R = 5 * A;
    REQUIRE(R[0] == 5);
    REQUIRE(R[1] == 5);
    REQUIRE(R[2] == 5);
    REQUIRE(R[3] == 5);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A * 5");
    R = A * 5;
    REQUIRE(R[0] == 5);
    REQUIRE(R[1] == 5);
    REQUIRE(R[2] == 5);
    REQUIRE(R[3] == 5);
  }
}

TEST_CASE("Dense: Add/Mul", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
  DenseMatrix<int> B(2, 2, {2, 2, 2, 2});
  DenseMatrix<int> C(2, 2, {3, 3, 3, 3});

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A + (B + C)");
    R = A + (B + C);
    REQUIRE(R(0, 0) == 6);
    REQUIRE(R(0, 1) == 6);
    REQUIRE(R(1, 0) == 6);
    REQUIRE(R(1, 1) == 6);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A * (B + C)");
    R = A * (B + C);
    REQUIRE(R(0, 0) == 10);
    REQUIRE(R(0, 1) == 10);
    REQUIRE(R(1, 0) == 10);
    REQUIRE(R(1, 1) == 10);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A + (B * C)");
    R = A + (B * C);
    REQUIRE(R(0, 0) == 13);
    REQUIRE(R(0, 1) == 13);
    REQUIRE(R(1, 0) == 13);
    REQUIRE(R(1, 1) == 13);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A * (B * C)");
    R = A * (B * C);
    REQUIRE(R(0, 0) == 24);
    REQUIRE(R(0, 1) == 24);
    REQUIRE(R(1, 0) == 24);
    REQUIRE(R(1, 1) == 24);
  }
}

TEST_CASE("Dense: Sub", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
  DenseMatrix<int> B(2, 2, {2, 2, 2, 2});

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = -A");
    R = -A;
    REQUIRE(R[0] == -1);
    REQUIRE(R[1] == -1);
    REQUIRE(R[2] == -1);
    REQUIRE(R[3] == -1);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A - B");
    R = A - B;
    REQUIRE(R[0] == -1);
    REQUIRE(R[1] == -1);
    REQUIRE(R[2] == -1);
    REQUIRE(R[3] == -1);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = 5 - A");
    R = 5 - A;
    REQUIRE(R[0] == -4);
    REQUIRE(R[1] == -4);
    REQUIRE(R[2] == -4);
    REQUIRE(R[3] == -4);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A - 5");
    R = A - 5;
    REQUIRE(R[0] == -4);
    REQUIRE(R[1] == -4);
    REQUIRE(R[2] == -4);
    REQUIRE(R[3] == -4);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A - -B");
    R = A - -B;
    REQUIRE(R[0] == 3);
    REQUIRE(R[1] == 3);
    REQUIRE(R[2] == 3);
    REQUIRE(R[3] == 3);
  }
}

TEST_CASE("Dense: transpose", "[dense]") {
  DenseMatrix<int> A(2, 2, {1, 2, 3, 1});
  DenseMatrix<int> B(2, 2, {1, 3, 2, 1});

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A)");
    R = transpose(A);
    REQUIRE(R(0, 0) == 1);
    REQUIRE(R(0, 1) == 3);
    REQUIRE(R(1, 0) == 2);
    REQUIRE(R(1, 1) == 1);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(transpose(A))");
    R = transpose(transpose(A));
    REQUIRE(R(0, 0) == 1);
    REQUIRE(R(0, 1) == 2);
    REQUIRE(R(1, 0) == 3);
    REQUIRE(R(1, 1) == 1);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A) + transpose(B)");
    R = transpose(A) + transpose(B);
    REQUIRE(R(0, 0) == 2);
    REQUIRE(R(0, 1) == 5);
    REQUIRE(R(1, 0) == 5);
    REQUIRE(R(1, 1) == 2);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A + B)");
    R = transpose(A + B);
    REQUIRE(R(0, 0) == 2);
    REQUIRE(R(0, 1) == 5);
    REQUIRE(R(1, 0) == 5);
    REQUIRE(R(1, 1) == 2);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A) * transpose(B)");
    R = transpose(A) * transpose(B);
    REQUIRE(R(0, 0) == 10);
    REQUIRE(R(0, 1) == 5);
    REQUIRE(R(1, 0) == 5);
    REQUIRE(R(1, 1) == 5);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A * B)");
    R = transpose(A * B);
    REQUIRE(R(0, 0) == 5);
    REQUIRE(R(0, 1) == 5);
    REQUIRE(R(1, 0) == 5);
    REQUIRE(R(1, 1) == 10);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A + transpose(B)");
    R = A + transpose(B);
    REQUIRE(R(0, 0) == 2);
    REQUIRE(R(0, 1) == 4);
    REQUIRE(R(1, 0) == 6);
    REQUIRE(R(1, 1) == 2);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A) + B");
    R = transpose(A) + B;
    REQUIRE(R(0, 0) == 2);
    REQUIRE(R(0, 1) == 6);
    REQUIRE(R(1, 0) == 4);
    REQUIRE(R(1, 1) == 2);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = A * transpose(B)");
    R = A * transpose(B);
    REQUIRE(R(0, 0) == 7);
    REQUIRE(R(0, 1) == 4);
    REQUIRE(R(1, 0) == 6);
    REQUIRE(R(1, 1) == 7);
  }

  {
    DenseMatrix<int> R(2, 2);
    TEST_DEBUG("R = transpose(A) * B");
    R = transpose(A) * B;
    REQUIRE(R(0, 0) == 7);
    REQUIRE(R(0, 1) == 6);
    REQUIRE(R(1, 0) == 4);
    REQUIRE(R(1, 1) == 7);
  }
}

TEST_CASE("Dense: jacobian", "[dense]") {
  RCP<const Symbol> x = symbol("x");
  RCP<const Symbol> y = symbol("y");

  SymbolicVector a({x, mul(x, y)});
  SymbolicVector b({x, y});
  SymbolicMatrix C(2, 2);
  C = integer(1);

  {
    SymbolicMatrix R(2, 2);
    TEST_DEBUG("R = jacobian(a, b)");
    R = jacobian(a, b);
    REQUIRE(eq(*R(0, 0), *integer(1)));
    REQUIRE(eq(*R(0, 1), *integer(0)));
    REQUIRE(eq(*R(1, 0), *y));
    REQUIRE(eq(*R(1, 1), *x));
  }

  // {
  //   SymbolicMatrix R(2, 2);
  //   TEST_DEBUG("R = C + jacobian(a, b)");
  //   R = C + jacobian(a, b);
  //   REQUIRE(eq(*R(0, 0), *integer(2)));
  //   REQUIRE(eq(*R(0, 1), *integer(1)));
  //   REQUIRE(eq(*R(1, 0), *add(y, integer(1))));
  //   REQUIRE(eq(*R(1, 1), *add(x, integer(1))));
  // }

  // {
  //   SymbolicMatrix R(2, 2);
  //   TEST_DEBUG("R = C * jacobian(a, b)");
  //   R = C * jacobian(a, b);
  //   REQUIRE(eq(*R(0, 0), *add(y, integer(1))));
  //   REQUIRE(eq(*R(0, 1), *x));
  //   REQUIRE(eq(*R(1, 0), *add(y, integer(1))));
  //   REQUIRE(eq(*R(1, 1), *x));
  // }

  {
    SymbolicMatrix R(2, 2);
    TEST_DEBUG("R = transpose(jacobian(a, b))");
    R = transpose(jacobian(a, b));
    REQUIRE(eq(*R(0, 0), *integer(1)));
    REQUIRE(eq(*R(0, 1), *y));
    REQUIRE(eq(*R(1, 0), *integer(0)));
    REQUIRE(eq(*R(1, 1), *x));
  }

  Vector<int> c({1, 1});
  Vector<int> d({1, 1});
  DenseMatrix<int> S(2, 2);

  // Fails!
  // S = jacobian(a, b);
  // S = jacobian(c, d);
  // R = jacobian(c, d);
}

TEST_CASE("Dense: DenseMatrix RCP<const Basic>", "[dense]") {
  SymbolicMatrix A(2, 2, {integer(1), integer(1), integer(1), integer(1)});
  SymbolicMatrix C(2, 2);

  // Assignment
  C = integer(5);

  REQUIRE(eq(*C(0, 0), *integer(5)));
  REQUIRE(eq(*C(0, 1), *integer(5)));
  REQUIRE(eq(*C(1, 0), *integer(5)));
  REQUIRE(eq(*C(1, 1), *integer(5)));

  C = A;

  REQUIRE(C == A);

  C(0, 0) = integer(2);

  REQUIRE(C != A);

  // // Addition
  // M = M + Q;
  //
  // REQUIRE(eq(*M(0, 0), *integer(3)));
  // REQUIRE(eq(*M(0, 1), *integer(4)));
  // REQUIRE(eq(*M(1, 0), *integer(6)));
  // REQUIRE(eq(*M(1, 1), *integer(8)));
  //
  // M = Q + Q + Q + Q;
  //
  // REQUIRE(eq(*M(0, 0), *integer(4)));
  // REQUIRE(eq(*M(0, 1), *integer(8)));
  // REQUIRE(eq(*M(1, 0), *integer(12)));
  // REQUIRE(eq(*M(1, 1), *integer(16)));
  //
  // M += integer(1);
  //
  // REQUIRE(eq(*M(0, 0), *integer(5)));
  // REQUIRE(eq(*M(0, 1), *integer(9)));
  // REQUIRE(eq(*M(1, 0), *integer(13)));
  // REQUIRE(eq(*M(1, 1), *integer(17)));
  //
  // // Multiplication
  // M = M * Q;
  //
  // REQUIRE(eq(*M(0, 0), *integer(32)));
  // REQUIRE(eq(*M(0, 1), *integer(46)));
  // REQUIRE(eq(*M(1, 0), *integer(64)));
  // REQUIRE(eq(*M(1, 1), *integer(94)));
  //
  // M = Q * Q * Q * Q;
  //
  // REQUIRE(eq(*M(0, 0), *integer(199)));
  // REQUIRE(eq(*M(0, 1), *integer(290)));
  // REQUIRE(eq(*M(1, 0), *integer(435)));
  // REQUIRE(eq(*M(1, 1), *integer(634)));
  //
  // M = Q + Q * Q + Q;
  //
  // REQUIRE(eq(*M(0, 0), *integer(9)));
  // REQUIRE(eq(*M(0, 1), *integer(14)));
  // REQUIRE(eq(*M(1, 0), *integer(21)));
  // REQUIRE(eq(*M(1, 1), *integer(30)));
  //
  // M = Q + (Q * Q) + Q;
  //
  // REQUIRE(eq(*M(0, 0), *integer(9)));
  // REQUIRE(eq(*M(0, 1), *integer(14)));
  // REQUIRE(eq(*M(1, 0), *integer(21)));
  // REQUIRE(eq(*M(1, 1), *integer(30)));
  //
  // SymbolicMatrix R(2, 3);
  //
  // R(0, 0) = integer(1);
  // R(0, 1) = integer(2);
  // R(0, 2) = integer(3);
  // R(1, 0) = integer(4);
  // R(1, 1) = integer(5);
  // R(1, 2) = integer(6);
  //
  // M = Q * R;
  //
  // REQUIRE(eq(*M(0, 0), *integer(9)));
  // REQUIRE(eq(*M(0, 1), *integer(12)));
  // REQUIRE(eq(*M(0, 2), *integer(15)));
  // REQUIRE(eq(*M(1, 0), *integer(19)));
  // REQUIRE(eq(*M(1, 1), *integer(26)));
  // REQUIRE(eq(*M(1, 2), *integer(33)));
}

TEST_CASE("Dense: DenseMatrix checks", "[dense]") {
  {
    DenseMatrix<int> A(2, 2, {1, 2, 2, 1});
    DenseMatrix<int> B(2, 2, {1, 2, 3, 1});

    REQUIRE(is_symmetric(A));
    REQUIRE(!is_symmetric(B));
  }

  {
    SymbolicMatrix A(2, 2, {integer(1), integer(2), integer(2), integer(1)});
    SymbolicMatrix B(2, 2, {integer(1), integer(2), integer(3), integer(1)});

    REQUIRE(is_symmetric(A));
    REQUIRE(!is_symmetric(B));
  }

  {
    DenseMatrix<int> A(2, 2, {1, 1, 0, 1});
    DenseMatrix<int> B(2, 2, {1, 0, 1, 1});

    REQUIRE(is_upper(A));
    REQUIRE(!is_upper(B));
  }

  {
    SymbolicMatrix A(2, 2, {integer(1), integer(1), integer(0), integer(1)});
    SymbolicMatrix B(2, 2, {integer(1), integer(0), integer(1), integer(1)});

    REQUIRE(is_upper(A));
    REQUIRE(!is_upper(B));
  }

  {
    DenseMatrix<int> A(2, 2, {1, 0, 1, 1});
    DenseMatrix<int> B(2, 2, {1, 1, 0, 1});

    REQUIRE(is_lower(A));
    REQUIRE(!is_lower(B));
  }

  {
    SymbolicMatrix A(2, 2, {integer(1), integer(0), integer(1), integer(1)});
    SymbolicMatrix B(2, 2, {integer(1), integer(1), integer(0), integer(1)});

    REQUIRE(is_lower(A));
    REQUIRE(!is_lower(B));
  }

}
