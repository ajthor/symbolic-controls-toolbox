#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <type_traits>

#include <symengine/basic.h>
#include <symengine/integer.h>
#include <symengine/symbol.h>

#include <math/math.hpp>
#include <math/traits/is_matrix.hpp>
#include <math/traits/is_dense_matrix.hpp>
#include <math/traits/is_vector.hpp>
#include <math/traits/is_expr.hpp>
#include <math/traits/is_symbolic.hpp>

using Controls::Math::Matrix;
using Controls::Math::DenseMatrix;
using Controls::Math::Vector;
using Controls::Math::Expression;
using Controls::Math::ExprAdd;
using Controls::Math::ExprMul;
using Controls::Math::ExprTranspose;
using Controls::Math::ExprJacobian;

using SymEngine::Basic;
using SymEngine::Integer;
using SymEngine::RCP;
using SymEngine::Symbol;

using Controls::Math::is_matrix;
using Controls::Math::is_matrix_t;
using Controls::Math::is_dense_matrix;
using Controls::Math::is_dense_matrix_t;
using Controls::Math::is_vector;
using Controls::Math::is_vector_t;
using Controls::Math::is_expr;
using Controls::Math::is_expr_t;
using Controls::Math::is_symbolic;
using Controls::Math::is_symbolic_t;

TEST_CASE("Type Traits: is_matrix", "[typetraits]") {
  REQUIRE(is_matrix<DenseMatrix<int>>::value);
  REQUIRE(is_matrix<Vector<int>>::value);
}

TEST_CASE("Type Traits: is_dense_matrix", "[typetraits]") {
  REQUIRE(is_matrix<DenseMatrix<int>>::value);
  REQUIRE(is_dense_matrix<DenseMatrix<int>>::value);
  REQUIRE(!is_dense_matrix<Vector<int>>::value);
  REQUIRE(is_dense_matrix<DenseMatrix<int>>::value);
}

TEST_CASE("Type Traits: is_vector", "[typetraits]") {
  REQUIRE(is_matrix<Vector<int>>::value);
  REQUIRE(is_vector<Vector<int>>::value);
  REQUIRE(!is_vector<DenseMatrix<int>>::value);
  REQUIRE(is_vector<Vector<int>>::value);
}

TEST_CASE("Type Traits: is_expr", "[typetraits]") {
  // REQUIRE(is_expr<Expression>::value);
  REQUIRE(is_expr<ExprAdd<DenseMatrix<int>, DenseMatrix<int>>>::value);
  REQUIRE(is_expr<ExprMul<DenseMatrix<int>, DenseMatrix<int>>>::value);
  REQUIRE(is_expr<ExprTranspose<DenseMatrix<int>>>::value);
  // REQUIRE(is_expr<ExprInverse<DenseMatrix<int>>>::value);
  // REQUIRE(is_expr<ExprJacobian>::value);
  REQUIRE(is_matrix<ExprAdd<DenseMatrix<int>, DenseMatrix<int>>>::value);
  REQUIRE(is_matrix<ExprMul<DenseMatrix<int>, DenseMatrix<int>>>::value);
  REQUIRE(is_matrix<ExprTranspose<DenseMatrix<int>>>::value);
  // REQUIRE(is_matrix<ExprInverse<DenseMatrix<int>>>::value);
  // REQUIRE(is_matrix<ExprJacobian>::value);
}

TEST_CASE("Type Traits: is_symbolic", "[typetraits]") {
  REQUIRE(!is_symbolic<DenseMatrix<int>>::value);
  REQUIRE(!is_symbolic<Vector<int>>::value);
  REQUIRE(is_symbolic<DenseMatrix<RCP<const Basic>>>::value);
  REQUIRE(is_symbolic<DenseMatrix<RCP<const Integer>>>::value);
  REQUIRE(is_symbolic<DenseMatrix<RCP<const Symbol>>>::value);
  REQUIRE(is_symbolic<Vector<RCP<const Basic>>>::value);
  REQUIRE(is_symbolic<Vector<RCP<const Integer>>>::value);
  REQUIRE(is_symbolic<Vector<RCP<const Symbol>>>::value);
}
