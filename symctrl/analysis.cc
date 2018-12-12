#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/subs.h>

#include "analysis.hpp"

using SymEngine::DenseMatrix;

namespace Controls {

// ----------------------------------------------------------------------
// Controllability
//
void ctrb(StateSpace &obj, DenseMatrix &result) {
  DenseMatrix A;
  DenseMatrix B;
  obj.get_A_matrix(A);
  obj.get_B_matrix(B);

  ctrb(A, B, result);
}
void ctrb(DenseMatrix &A,
          DenseMatrix &B,
          DenseMatrix &result) {

  // TODO: Add dimension checking.
  unsigned n = A.ncols();
  unsigned m = B.ncols();
  DenseMatrix M;

  result = DenseMatrix(B);
  M = DenseMatrix(result);

  int k = 0;
  for(k = m; k < n*m; k += m) {
    // Keep a running matrix.
    A.mul_matrix(M, M);
    result.row_join(M);
  }
}

int ctrb_rank(StateSpace &obj) {
  DenseMatrix co;
  ctrb(obj, co);
  //
  // SymEngine::permutelist pl;
  // SymEngine::pivoted_gaussian_elimination(co, result, pl);
  return co.rank();
}

// ----------------------------------------------------------------------
// Observability
//
void obsv(StateSpace &obj, DenseMatrix &result) {
  DenseMatrix A;
  DenseMatrix C;
  obj.get_A_matrix(A);
  obj.get_C_matrix(C);

  obsv(A, C, result);
}
void obsv(DenseMatrix &A,
          DenseMatrix &C,
          DenseMatrix &result) {

  // TODO: Add dimension checking.
  unsigned n = A.nrows();
  unsigned p = C.nrows();
  DenseMatrix M;

  result = DenseMatrix(C);
  M = DenseMatrix(result);

  int k = 0;
  for(k = p; k < n*p; k += p) {
    // Keep a running matrix.
    M.mul_matrix(A, M);
    result.col_join(M);
  }
}

} // Controls
