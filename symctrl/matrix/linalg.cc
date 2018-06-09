#include <symengine/add.h>
#include <symengine/pow.h>

#include "linalg.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Helper Functions
//
void submatrix_from_vec(SymEngine::vec_basic &v,
                        size_t row_start, size_t row_end,
                        size_t col_start, size_t col_end,
                        SymEngine::vec_basic &result) {
  //
  size_t row, col, i, j, idx;

  row = row_end - row_start;
  col = col_end - col_start;
  // Fix for simgle row/column.
  if(row == 0) {
    row_end = row_start + 1;
  }
  if(col == 0) {
    col_end = col_start + 1;
  }
  // row = v.nrows();
  // col = v.ncols();

  result = SymEngine::vec_basic(row*col);
  idx = 0;
  for(i = row_start; i < row_end; i++) {
    for(j = col_start; j < col_end; j++) {
      result[idx++] = v[i*col_end + j];
    }
  }
}

void vec_to_submatrix(SymEngine::vec_basic &v,
                      size_t row_start, size_t row_end,
                      size_t col_start, size_t col_end,
                      SymEngine::vec_basic &result) {
  //
  size_t row, col, i, j, idx;

  row = row_end - row_start;
  col = col_end - col_start;
  // Fix for simgle row/column.
  if(row == 0) {
    row_end = row_start + 1;
  }
  if(col == 0) {
    col_end = col_start + 1;
  }

  idx = 0;
  for(i = row_start; i < row_end; i++) {
    for(j = col_start; j < col_end; j++) {
      result[i*col_end + j] = v[idx++];
    }
  }
}

void vec_printf(SymEngine::vec_basic &v) {
  SymEngine::DenseMatrix M = SymEngine::DenseMatrix(v.size(), 1, {v});
  printf("%s\n", M.__str__().c_str());
}
void vec_printf(size_t r, size_t c, SymEngine::vec_basic &v) {
  SymEngine::DenseMatrix M = SymEngine::DenseMatrix(r, c, {v});
  printf("%s\n", M.__str__().c_str());
}
void mat_printf(SymEngine::DenseMatrix &M) {
  printf("%s\n", M.__str__().c_str());
}

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
// Vector Multiplication
//
void mul_vec(SymEngine::vec_basic &v, SymEngine::DenseMatrix &M) {
  size_t i, j;
  size_t len = v.size();
  SymEngine::vec_basic u = SymEngine::vec_basic(len*len);

  for(i = 0; i < len; i++) { // row
    for(j = 0; j < len; j++) { // col
      u[i*len + j] = SymEngine::mul(v[i], v[j]);
    }
  }

  M = SymEngine::DenseMatrix(len, len, {u});
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
