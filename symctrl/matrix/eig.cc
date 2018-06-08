#include <symengine/add.h>
#include <symengine/pow.h>

#include "eig.hpp"
#include "linalg.hpp"

namespace Controls {

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

} // Controls
