#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <type_traits>

#include <symengine/basic.h>
#include <symengine/integer.h>
#include <symengine/symbol.h>

#include <symctrl/math/math.hpp>
#include <symctrl/type_traits/is_default.hpp>
#include <symctrl/type_traits/is_scalar.hpp>
#include <symctrl/type_traits/is_symbolic.hpp>
#include <symctrl/math/matrix/type_traits/is_constant.hpp>
#include <symctrl/math/matrix/type_traits/is_dense.hpp>
#include <symctrl/math/matrix/type_traits/is_expr.hpp>
#include <symctrl/math/matrix/type_traits/is_matrix.hpp>
#include <symctrl/math/matrix/type_traits/is_static.hpp>
#include <symctrl/math/matrix/type_traits/is_vector.hpp>

using Controls::Math::ConstantMatrix;
using Controls::Math::DenseMatrix;
using Controls::Math::Expression;
using Controls::Math::ExprAdd;
using Controls::Math::ExprSub;
using Controls::Math::ExprMul;
using Controls::Math::ExprInverse;
using Controls::Math::ExprNeg;
using Controls::Math::ExprTranspose;
using Controls::Math::ExprUnary;
using Controls::Math::Identity;
using Controls::Math::Matrix;
using Controls::Math::Ones;
using Controls::Math::StaticDense;
using Controls::Math::StaticVector;
using Controls::Math::Vector;
using Controls::Math::Zeros;

using SymEngine::Basic;
using SymEngine::Integer;
using SymEngine::RCP;
using SymEngine::Symbol;

using Controls::Math::is_constant;
using Controls::Math::is_constant_t;
using Controls::is_default;
using Controls::Math::is_dense;
using Controls::Math::is_dense_t;
using Controls::Math::is_expr;
using Controls::Math::is_expr_t;
using Controls::Math::is_matrix;
using Controls::Math::is_matrix_t;
using Controls::is_scalar;
using Controls::is_scalar_t;
using Controls::Math::is_static;
using Controls::Math::is_static_t;
using Controls::is_symbolic;
using Controls::is_symbolic_t;
using Controls::Math::is_vector;
using Controls::Math::is_vector_t;

TEST_CASE("Type Traits: is_constant", "[typetraits]") {
  REQUIRE(is_constant<ConstantMatrix<int, 2, 2, 1>>::value);
  REQUIRE(is_constant<Identity<int, 2, 2>>::value);
  REQUIRE(is_constant<Ones<int, 2, 2>>::value);
  REQUIRE(is_constant<Zeros<int, 2, 2>>::value);
  REQUIRE(!is_constant<DenseMatrix<int>>::value);
}

TEST_CASE("Type Traits: is_dense", "[typetraits]") {
  REQUIRE(is_dense<DenseMatrix<int>>::value);
  REQUIRE(!is_dense<Vector<int>>::value);
}

TEST_CASE("Type Traits: is_default", "[typetraits]") {
  {
    int v = int();
    REQUIRE(is_default(v));
  }
  {
    float v = float();
    REQUIRE(is_default(v));
  }
  {
    double v = double();
    REQUIRE(is_default(v));
  }
  // int a = 0;
  // REQUIRE(is_default_value<int, &a>::value);
  // REQUIRE(!is_default_value<int, 1>::value);
  // std::cout << Controls::default_value<double>::value << '\n';
  // REQUIRE(is_default_value<double, 0>::value);
  // REQUIRE(!is_default_value<double, 1.0>::value);
}

TEST_CASE("Type Traits: is_expr", "[typetraits]") {
  REQUIRE(is_expr<ExprAdd<DenseMatrix<int>, DenseMatrix<int>>>::value);
  REQUIRE(is_expr<ExprSub<DenseMatrix<int>, DenseMatrix<int>>>::value);
  REQUIRE(is_expr<ExprMul<DenseMatrix<int>, DenseMatrix<int>>>::value);
  REQUIRE(is_expr<ExprInverse<DenseMatrix<int>>>::value);
  REQUIRE(is_expr<ExprNeg<DenseMatrix<int>>>::value);
  REQUIRE(is_expr<ExprTranspose<DenseMatrix<int>>>::value);
  REQUIRE(is_expr<ExprUnary<DenseMatrix<int>>>::value);
}

TEST_CASE("Type Traits: is_matrix", "[typetraits]") {
  // Constant
  REQUIRE(is_matrix<ConstantMatrix<int, 2, 2, 1>>::value);
  REQUIRE(is_matrix<Identity<int, 2, 2>>::value);
  REQUIRE(is_matrix<Ones<int, 2, 2>>::value);
  REQUIRE(is_matrix<Zeros<int, 2, 2>>::value);

  // Dense
  REQUIRE(is_matrix<DenseMatrix<int>>::value);

  // Expr
  REQUIRE(is_matrix<ExprAdd<DenseMatrix<int>, DenseMatrix<int>>>::value);
  REQUIRE(is_matrix<ExprSub<DenseMatrix<int>, DenseMatrix<int>>>::value);
  REQUIRE(is_matrix<ExprMul<DenseMatrix<int>, DenseMatrix<int>>>::value);
  REQUIRE(is_matrix<ExprInverse<DenseMatrix<int>>>::value);
  REQUIRE(is_matrix<ExprNeg<DenseMatrix<int>>>::value);
  REQUIRE(is_matrix<ExprTranspose<DenseMatrix<int>>>::value);
  REQUIRE(is_matrix<ExprUnary<DenseMatrix<int>>>::value);

  // Static
  REQUIRE(is_matrix<StaticDense<int, 2, 2>>::value);
  REQUIRE(is_matrix<StaticVector<int, 2, 1>>::value);

  // Vector
  REQUIRE(is_matrix<Vector<int>>::value);
}

TEST_CASE("Type Traits: is_scalar", "[typetraits]") {
  REQUIRE(is_scalar<int>::value);
  REQUIRE(is_scalar<double>::value);
  REQUIRE(is_scalar<float>::value);
}

TEST_CASE("Type Traits: is_static", "[typetraits]") {
  REQUIRE(is_static<StaticDense<int, 2, 2>>::value);
  REQUIRE(is_static<StaticVector<int, 2, 1>>::value);
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

TEST_CASE("Type Traits: is_vector", "[typetraits]") {
  REQUIRE(is_vector<Vector<int>>::value);
  REQUIRE(!is_vector<DenseMatrix<int>>::value);
}
