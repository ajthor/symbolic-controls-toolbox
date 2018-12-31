#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <type_traits>

#include <symengine/basic.h>
#include <symengine/integer.h>
#include <symengine/symbol.h>

#include <symctrl/math/math.hpp>
#include <symctrl/traits/is_matrix.hpp>
#include <symctrl/traits/is_dense.hpp>
#include <symctrl/traits/is_vector.hpp>
#include <symctrl/traits/is_expr.hpp>
#include <symctrl/traits/is_symbolic.hpp>
#include <symctrl/traits/is_constant.hpp>
#include <symctrl/traits/is_scalar.hpp>

using Controls::Math::Matrix;
using Controls::Math::DenseMatrix;
using Controls::Math::Vector;
using Controls::Math::StaticMatrix;
using Controls::Math::ConstantMatrix;
using Controls::Math::Identity;
using Controls::Math::Ones;
using Controls::Math::Zeros;
using Controls::Math::Expression;
using Controls::Math::ExprAdd;
using Controls::Math::ExprMul;
using Controls::Math::ExprTranspose;
// using Controls::Math::ExprJacobian;

using SymEngine::Basic;
using SymEngine::Integer;
using SymEngine::RCP;
using SymEngine::Symbol;

using Controls::Math::is_matrix;
using Controls::Math::is_matrix_t;
using Controls::Math::is_dense;
using Controls::Math::is_dense_t;
using Controls::Math::is_vector;
using Controls::Math::is_vector_t;
using Controls::Math::is_expr;
using Controls::Math::is_expr_t;
using Controls::Math::is_symbolic;
using Controls::Math::is_symbolic_t;
using Controls::Math::is_constant;
using Controls::Math::is_constant_t;
using Controls::Math::is_scalar;
using Controls::Math::is_scalar_t;

TEST_CASE("Type Traits: is_matrix", "[typetraits]") {
  REQUIRE(is_matrix<DenseMatrix<int>>::value);
  REQUIRE(is_matrix<Vector<int>>::value);
}

TEST_CASE("Type Traits: is_dense", "[typetraits]") {
  REQUIRE(is_matrix<DenseMatrix<int>>::value);
  REQUIRE(is_dense<DenseMatrix<int>>::value);
  REQUIRE(!is_dense<Vector<int>>::value);
}

TEST_CASE("Type Traits: is_vector", "[typetraits]") {
  REQUIRE(is_matrix<Vector<int>>::value);
  REQUIRE(is_vector<Vector<int>>::value);
  REQUIRE(!is_vector<DenseMatrix<int>>::value);
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

TEST_CASE("Type Traits: is_constant", "[typetraits]") {
  REQUIRE(is_matrix<ConstantMatrix<int, 2, 2, 1>>::value);
  REQUIRE(is_matrix<Identity<int, 2, 2>>::value);
  REQUIRE(is_matrix<Ones<int, 2, 2>>::value);
  REQUIRE(is_matrix<Zeros<int, 2, 2>>::value);
  REQUIRE(is_constant<ConstantMatrix<int, 2, 2, 1>>::value);
  REQUIRE(is_constant<Identity<int, 2, 2>>::value);
  REQUIRE(is_constant<Ones<int, 2, 2>>::value);
  REQUIRE(is_constant<Zeros<int, 2, 2>>::value);
  REQUIRE(!is_constant<DenseMatrix<int>>::value);
}

TEST_CASE("Type Traits: is_scalar", "[typetraits]") {
  REQUIRE(is_scalar<int>::value);
  REQUIRE(is_scalar<double>::value);
  REQUIRE(is_scalar<float>::value);
}
