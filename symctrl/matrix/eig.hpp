#ifndef MODELS_UTILS_EIG_HPP
#define MODELS_UTILS_EIG_HPP

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

namespace Controls {

// Check if matrix is square.
bool is_square(SymEngine::MatrixBase &A);

SymEngine::RCP<const SymEngine::Basic> norm2(SymEngine::vec_basic &v);
void normalize(SymEngine::vec_basic &v);

// Should this use the Schur decomposition, or the polynomial solve method?
void eigenvalues(SymEngine::DenseMatrix &A,
                         SymEngine::vec_basic &l,
                         SymEngine::DenseMatrix &v);

// Use eigenvalues or the Schur decomposition to compute eigenvectors.
void eigenvectors();

// Compute the jordan form using eigenvector matrix.
void compute_jordan_form();

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

#endif /* end of include guard: MODELS_UTILS_EIG_HPP */
