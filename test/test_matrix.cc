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

TEST_CASE("Matrix: DenseMatrix", "[matrix]") {
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

TEST_CASE("Matrix: DenseMatrix operations", "[matrix]") {
  // // Addition
  // std::cout << "R = R + M" << '\n';
  // R = R + M;
  //
  // REQUIRE(R(0, 0) == 3);
  // REQUIRE(R(0, 1) == 4);
  // REQUIRE(R(1, 0) == 6);
  // REQUIRE(R(1, 1) == 8);
  //
  // std::cout << "R = M + R" << '\n';
  // R = M + R;
  //
  // REQUIRE(R(0, 0) == 4);
  // REQUIRE(R(0, 1) == 6);
  // REQUIRE(R(1, 0) == 9);
  // REQUIRE(R(1, 1) == 12);
  //
  // std::cout << "R = M + M + M + M" << '\n';
  // R = M + M + M + M;
  //
  // REQUIRE(R(0, 0) == 4);
  // REQUIRE(R(0, 1) == 8);
  // REQUIRE(R(1, 0) == 12);
  // REQUIRE(R(1, 1) == 16);
  //
  // R += 1;
  //
  // REQUIRE(R(0, 0) == 5);
  // REQUIRE(R(0, 1) == 9);
  // REQUIRE(R(1, 0) == 13);
  // REQUIRE(R(1, 1) == 17);
  //
  // // Multiplication
  // std::cout << "R = R * M" << '\n';
  // R = R * M;
  //
  // REQUIRE(R(0, 0) == 32);
  // REQUIRE(R(0, 1) == 46);
  // REQUIRE(R(1, 0) == 64);
  // REQUIRE(R(1, 1) == 94);
  //
  // // std::cout << "R = M * R" << '\n';
  // // R = M * R;
  // //
  // // REQUIRE(R(0, 0) == 31);
  // // REQUIRE(R(0, 1) == 43);
  // // REQUIRE(R(1, 0) == 67);
  // // REQUIRE(R(1, 1) == 95);
  //
  // std::cout << "R = Q + Q + Q + Q" << '\n';
  // R = Q + Q + Q + Q;
  //
  // REQUIRE(R(0, 0) == 8);
  // REQUIRE(R(0, 1) == 12);
  // REQUIRE(R(1, 0) == 16);
  // REQUIRE(R(1, 1) == 20);
  //
  // // std::cout << "R = Q * Q * Q * Q" << '\n';
  // // R = Q * Q * Q * Q;
  // //
  // // REQUIRE(R(0, 0) == 199);
  // // REQUIRE(R(0, 1) == 290);
  // // REQUIRE(R(1, 0) == 435);
  // // REQUIRE(R(1, 1) == 634);

  // std::cout << "R = Q + Q * Q + Q" << '\n';
  // R = Q + Q * Q + Q;
  //
  // REQUIRE(R(0, 0) == 9);
  // REQUIRE(R(0, 1) == 14);
  // REQUIRE(R(1, 0) == 21);
  // REQUIRE(R(1, 1) == 30);

  // std::cout << "R = Q + (Q * Q) + Q" << '\n';
  // R = Q + (Q * Q) + Q;
  //
  // REQUIRE(R(0, 0) == 9);
  // REQUIRE(R(0, 1) == 14);
  // REQUIRE(R(1, 0) == 21);
  // REQUIRE(R(1, 1) == 30);

  DenseMatrix<int> A(2, 2, {1, 1, 1, 1});
  DenseMatrix<int> B(2, 2, {2, 2, 2, 2});
  DenseMatrix<int> C(2, 2, {3, 3, 3, 3});
  DenseMatrix<int> R(2, 2);

  std::cout << "R = A + (B + C)" << '\n';
  R = A + (B + C);

  REQUIRE(R(0, 0) == 6);
  REQUIRE(R(0, 1) == 6);
  REQUIRE(R(1, 0) == 6);
  REQUIRE(R(1, 1) == 6);

  std::cout << "R = A * (B + C)" << '\n';
  R = A * (B + C);

  REQUIRE(R(0, 0) == 10);
  REQUIRE(R(0, 1) == 10);
  REQUIRE(R(1, 0) == 10);
  REQUIRE(R(1, 1) == 10);

  std::cout << "R = A + (B * C)" << '\n';
  R = A + (B * C);

  REQUIRE(R(0, 0) == 13);
  REQUIRE(R(0, 1) == 13);
  REQUIRE(R(1, 0) == 13);
  REQUIRE(R(1, 1) == 13);

  std::cout << "R = A * (B * C)" << '\n';
  R = A * (B * C);

  REQUIRE(R(0, 0) == 24);
  REQUIRE(R(0, 1) == 24);
  REQUIRE(R(1, 0) == 24);
  REQUIRE(R(1, 1) == 24);

  std::cout << "R = A + B + C + B + A" << '\n';
  R = A + B + C + B + A;

  REQUIRE(R(0, 0) == 9);
  REQUIRE(R(0, 1) == 9);
  REQUIRE(R(1, 0) == 9);
  REQUIRE(R(1, 1) == 9);

  std::cout << "R = A * B * C * B * A" << '\n';
  R = A * B * C * B * A;

  REQUIRE(R(0, 0) == 192);
  REQUIRE(R(0, 1) == 192);
  REQUIRE(R(1, 0) == 192);
  REQUIRE(R(1, 1) == 192);

  // std::cout << "A + B + C * A * B * C" << '\n';
  // R = A + B + C * A * B * C;
  //
  // REQUIRE(R(0, 0) == 147);
  // REQUIRE(R(0, 1) == 147);
  // REQUIRE(R(1, 0) == 147);
  // REQUIRE(R(1, 1) == 147);

  // std::cout << "A * B * C * A + B + C" << '\n';
  // R = A * B * C + A + B + C;
  //
  // REQUIRE(R(0, 0) == 30);
  // REQUIRE(R(0, 1) == 30);
  // REQUIRE(R(1, 0) == 30);
  // REQUIRE(R(1, 1) == 30);
}

TEST_CASE("Matrix: DenseMatrix RCP<const Basic>", "[matrix]") {
  SymbolicMatrix A(2, 2, {integer(1),
                                          integer(1),
                                          integer(1),
                                          integer(1)});
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

TEST_CASE("Matrix: DenseMatrix transpose", "[matrix]") {
  DenseMatrix<int> A(2, 2, {1, 2, 3, 1});
  DenseMatrix<int> B(2, 2, {1, 3, 2, 1});
  DenseMatrix<int> C(2, 2, {2, 5, 5, 2});
  DenseMatrix<int> R(2, 2);

  std::cout << "R = transpose(A)" << '\n';
  R = transpose(A);

  REQUIRE(R == B);

  std::cout << "R = transpose(transpose(A))" << '\n';
  R = transpose(transpose(A));

  REQUIRE(R == A);

  std::cout << "R = transpose(A) + transpose(B)" << '\n';
  R = transpose(A) + transpose(B);

  REQUIRE(R == C);

  std::cout << "R = transpose(A + B)" << '\n';
  R = transpose(A + B);

  REQUIRE(R == C);

  std::cout << "R = transpose(A) * transpose(B)" << '\n';
  R = transpose(A) * transpose(B);

  REQUIRE(R(0, 0) == 10);
  REQUIRE(R(0, 1) == 5);
  REQUIRE(R(1, 0) == 5);
  REQUIRE(R(1, 1) == 5);

  std::cout << "R = transpose(A * B)" << '\n';
  R = transpose(A * B);

  REQUIRE(R(0, 0) == 5);
  REQUIRE(R(0, 1) == 5);
  REQUIRE(R(1, 0) == 5);
  REQUIRE(R(1, 1) == 10);

  std::cout << "R = A + transpose(B)" << '\n';
  R = A + transpose(B);

  REQUIRE(R(0, 0) == 2);
  REQUIRE(R(0, 1) == 4);
  REQUIRE(R(1, 0) == 6);
  REQUIRE(R(1, 1) == 2);

  std::cout << "R = transpose(A) + B" << '\n';
  R = transpose(A) + B;

  REQUIRE(R(0, 0) == 2);
  REQUIRE(R(0, 1) == 6);
  REQUIRE(R(1, 0) == 4);
  REQUIRE(R(1, 1) == 2);

  std::cout << "R = A * transpose(B)" << '\n';
  R = A * transpose(B);

  REQUIRE(R(0, 0) == 7);
  REQUIRE(R(0, 1) == 4);
  REQUIRE(R(1, 0) == 6);
  REQUIRE(R(1, 1) == 7);

  std::cout << "R = transpose(A) * B" << '\n';
  R = transpose(A) * B;

  REQUIRE(R(0, 0) == 7);
  REQUIRE(R(0, 1) == 6);
  REQUIRE(R(1, 0) == 4);
  REQUIRE(R(1, 1) == 7);
}

TEST_CASE("Matrix: Vector", "[matrix]") {
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

TEST_CASE("Matrix: Vector operations", "[matrix]") {
  Vector<int> a({1, 1});
  Vector<int> b({2, 2});
  Vector<int> c({3, 3});
  Vector<int> r(2);

  // Addition
  r = a + b;

  REQUIRE(r == c);

  r = a + a + a;

  REQUIRE(r == c);
}

TEST_CASE("Matrix: Vector RCP<const Basic>", "[matrix]") {
  Vector<RCP<const Basic>> a({integer(1), integer(1)});
  Vector<RCP<const Basic>> r(2);

  // Assignment
  r = integer(5);

  REQUIRE(eq(*r[0], *integer(5)));
  REQUIRE(eq(*r[1], *integer(5)));

  r = a;

  REQUIRE(r == a);

  r[0] = integer(2);

  REQUIRE(r != a);

  // // Addition
  // v = v + w;
  //
  // REQUIRE(eq(*v[0], *integer(3)));
  // REQUIRE(eq(*v[1], *integer(4)));
  //
  // v = w + w + w + w;
  //
  // REQUIRE(eq(*v[0], *integer(4)));
  // REQUIRE(eq(*v[1], *integer(8)));
}

TEST_CASE("Matrix: Vector transpose", "[matrix]") {
  Vector<int> a({1, 2});
  Vector<int> b({2, 3});
  Vector<int> r(2);

  r = transpose(a);

  REQUIRE(r != a);

  REQUIRE(r.nrows() == 1);
  REQUIRE(r.ncols() == 2);
  REQUIRE(r[0] == 1);
  REQUIRE(r[1] == 2);

  r = transpose(transpose(a));

  REQUIRE(r == a);

  REQUIRE(r.nrows() == 2);
  REQUIRE(r.ncols() == 1);
  REQUIRE(r[0] == 1);
  REQUIRE(r[1] == 2);
}

TEST_CASE("Matrix: DenseMatrix jacobian", "[matrix]") {
  RCP<const Symbol> x = symbol("x");
  RCP<const Symbol> y = symbol("y");

  SymbolicVector a({x, mul(x, y)});
  SymbolicVector b({x, y});
  SymbolicMatrix C(2, 2);
  C = integer(1);

  SymbolicMatrix R(2, 2);

  std::cout << "R = jacobian(a, b)" << '\n';
  R = jacobian(a, b);

  REQUIRE(eq(*R(0, 0), *integer(1)));
  REQUIRE(eq(*R(0, 1), *integer(0)));
  REQUIRE(eq(*R(1, 0), *y));
  REQUIRE(eq(*R(1, 1), *x));

  std::cout << "R = C + jacobian(a, b)" << '\n';
  R = C + jacobian(a, b);

  REQUIRE(eq(*R(0, 0), *integer(2)));
  REQUIRE(eq(*R(0, 1), *integer(1)));
  REQUIRE(eq(*R(1, 0), *add(y, integer(1))));
  REQUIRE(eq(*R(1, 1), *add(x, integer(1))));

  std::cout << "R = C * jacobian(a, b)" << '\n';
  R = C * jacobian(a, b);

  REQUIRE(eq(*R(0, 0), *add(y, integer(1))));
  REQUIRE(eq(*R(0, 1), *x));
  REQUIRE(eq(*R(1, 0), *add(y, integer(1))));
  REQUIRE(eq(*R(1, 1), *x));

  std::cout << "R = transpose(jacobian(a, b))" << '\n';
  R = transpose(jacobian(a, b));

  REQUIRE(eq(*R(0, 0), *integer(1)));
  REQUIRE(eq(*R(0, 1), *y));
  REQUIRE(eq(*R(1, 0), *integer(0)));
  REQUIRE(eq(*R(1, 1), *x));

  Vector<int> c({1, 1});
  Vector<int> d({1, 1});
  DenseMatrix<int> S(2, 2);

  // Fails!
  // S = jacobian(a, b);
  // S = jacobian(c, d);
  // R = jacobian(c, d);
}

TEST_CASE("Matrix: DenseMatrix checks", "[matrix]") {
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
