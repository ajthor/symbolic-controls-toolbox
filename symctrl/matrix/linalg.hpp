#ifndef SYMCTRL_MATRIX_LINALG_HPP
#define SYMCTRL_MATRIX_LINALG_HPP

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

namespace Controls {

// Helper Functions
void submatrix_from_vec(SymEngine::vec_basic &M,
                        size_t row_start, size_t row_end,
                        size_t col_start, size_t col_end,
                        SymEngine::vec_basic &result);

void vec_to_submatrix(SymEngine::vec_basic &v,
                      size_t row_start, size_t row_end,
                      size_t col_start, size_t col_end,
                      SymEngine::vec_basic &result);

void vec_printf(SymEngine::vec_basic &v);
void vec_printf(size_t r, size_t c, SymEngine::vec_basic &v);
void mat_printf(SymEngine::DenseMatrix &M);

// Check if matrix is square.
bool is_square(SymEngine::MatrixBase &A);

bool is_Hurwirz(SymEngine::MatrixBase &A);
bool is_Schur(SymEngine::MatrixBase &A);

// Vector norm.
SymEngine::RCP<const SymEngine::Basic> norm2(SymEngine::vec_basic &v);

// Vector normalization. V/|V|
void normalize(SymEngine::vec_basic &v);

// Vector multiplication. V*V'
void mul_vec(SymEngine::vec_basic &v, SymEngine::DenseMatrix &M);

// Householder
void householder_reflector(SymEngine::vec_basic &u);

void householder_transform_l(SymEngine::DenseMatrix &A,
                             SymEngine::vec_basic &u);
void householder_transform_l(SymEngine::DenseMatrix &A,
                             SymEngine::DenseMatrix &M);

void householder_transform_r(SymEngine::DenseMatrix &A,
                             SymEngine::vec_basic &u);
void householder_transform_r(SymEngine::DenseMatrix &A,
                             SymEngine::DenseMatrix &M);

// Hessenberg
void hessenberg(SymEngine::DenseMatrix &A,
                SymEngine::DenseMatrix &result);

// Schur
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
