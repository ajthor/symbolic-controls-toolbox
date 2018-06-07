#include <symengine/add.h>
#include <symengine/pow.h>

#include "eig.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Is Square
//
bool is_square(SymEngine::MatrixBase &A) {
  return (A.nrows() == A.ncols());
}

// ----------------------------------------------------------------------
// 2-Norm
//
SymEngine::RCP<const SymEngine::Basic> norm2(SymEngine::vec_basic &v) {
  SymEngine::RCP<const SymEngine::Basic> t = SymEngine::zero;
  int i = 0;
  for(i = 0; i < v.size(); i++) {
    t = SymEngine::add(t, SymEngine::pow(v[i], SymEngine::integer(2)));
  }
  t = SymEngine::pow(t, SymEngine::div(SymEngine::one, SymEngine::integer(2)));

  return t;
}

// ----------------------------------------------------------------------
// Vector Normalization
//
// v = v/|v|
void normalize(SymEngine::vec_basic &v) {
  SymEngine::RCP<const SymEngine::Basic> t = norm2(v);
  int i = 0;
  for(i = 0; i < v.size(); i++) {
    v[i] = SymEngine::div(v[i], t);
  }
}

// ----------------------------------------------------------------------
// Eigenvalues
//
void eigenvalues(SymEngine::DenseMatrix &A,
                 SymEngine::vec_basic &l,
                 SymEngine::DenseMatrix &V) {
  // TODO: Perform squareness checking.
  size_t n = A.ncols();

  SymEngine::DenseMatrix U, T;

  U = SymEngine::DenseMatrix(n, n);
  T = SymEngine::DenseMatrix(n, n);

  // Compute the Schur decomposition.
  schur(A, V, T);

  int i = 0;
  for(i = 0; i < n; i++) {
    l.push_back(T.get(i, i));
  }
}

// ----------------------------------------------------------------------
// Companion Matix
//
// The Frobenius companion matrix of a monic polynomial.
void companion_matrix(SymEngine::vec_basic &c, SymEngine::DenseMatrix &result) {
  size_t n = c.size();
  SymEngine::DenseMatrix A, B;

  result = SymEngine::DenseMatrix(1, n - 1);
  A = SymEngine::DenseMatrix(1, n - 1);
  B = SymEngine::DenseMatrix(n, 1, {c});

  SymEngine::zeros(result);
  SymEngine::eye(A);
  result.col_join(A);
  result.row_join(B);
}

} // Controls
