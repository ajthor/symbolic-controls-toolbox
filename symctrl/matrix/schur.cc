// #include <symengine/add.h>
// #include <symengine/pow.h>

#include "linalg.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Schur
//
void schur(SymEngine::DenseMatrix &A,
           SymEngine::DenseMatrix &U,
           SymEngine::DenseMatrix &T,
           size_t n_iter) {
  unsigned row = A.nrows();
  unsigned col = A.ncols();

  // TODO: Perform squareness checking.
  if(!is_square(A)) {
    // error
  }

  // TODO: Perform numerical checking.
  size_t i, j;
  for(i = 0; i < row; i++) {
    for(j = 0; j < col; j++) {
      if(!SymEngine::is_a_Number(*A.get(i, j))) {
        // error
      }
    }
  }

  SymEngine::DenseMatrix Q, R, W, V;
  Q = SymEngine::DenseMatrix(row, col);
  R = SymEngine::DenseMatrix(row, col);

  W = SymEngine::DenseMatrix(A);
  V = SymEngine::DenseMatrix(row, col);
  SymEngine::eye(V);

  for(i = 0; i < n_iter; i++) {
    QR(W, Q, R);
    R.mul_matrix(Q, W);
    V.mul_matrix(Q, V);

    // TODO: Convert to tolerance checking.
    // Absolute difference is less than some parameter.
  }

  U = V;
  T = W;
}

} // Controls
