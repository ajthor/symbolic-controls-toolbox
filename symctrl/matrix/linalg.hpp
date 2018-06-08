#ifndef SYMCTRL_MATRIX_LINALG_HPP
#define SYMCTRL_MATRIX_LINALG_HPP

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

namespace Controls {

// Check if matrix is square.
bool is_square(SymEngine::MatrixBase &A);

bool is_Hurwirz(SymEngine::MatrixBase &A);
bool is_Schur(SymEngine::MatrixBase &A);

SymEngine::RCP<const SymEngine::Basic> norm2(SymEngine::vec_basic &v);
void normalize(SymEngine::vec_basic &v);

void hessenberg(SymEngine::DenseMatrix &A,
                SymEngine::DenseMatrix &result);

void schur(SymEngine::DenseMatrix &A,
           SymEngine::DenseMatrix &U,
           SymEngine::DenseMatrix &T,
           size_t n_iter = 10);

// Evaluate matrix to find reduced row echelon form.
// Gauss-Jordan elimination with partial pivoting.
void rref();
// Use rref to find rank? Or some rank-revealing decomposition RRQR?
void rank();

void companion_matrix(SymEngine::vec_basic &c, SymEngine::DenseMatrix &result);

} // Controls

#endif /* end of include guard: SYMCTRL_MATRIX_LINALG_HPP */
