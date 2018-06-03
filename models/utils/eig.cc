#include <symengine/add.h>
#include <symengine/pow.h>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

#include "eig.hpp"

namespace Controls {

// void compute_eigenvalues(SymEngine::DenseMatrix &A,
//                          SymEngine::vec_basic &l,
//                          SymEngine::vec_basic &v) {
//   //
//
//   size_t n = A.ncols();
//
//   SymEngine::DenseMatrix Q, R;
//
//   Q = SymEngine::DenseMatrix(n, n);
//   R = SymEngine::DenseMatrix(n, n);
//   // Compute the QR decomposition.
//   SymEngine::QR(A, Q, R);
//
//   int i = 0;
//   for(i = 0; i < n; i++) {
//     v.push_back()
//   }
// }

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
// Hessenberg
//
void compute_hessenberg(SymEngine::DenseMatrix &A,
                        SymEngine::DenseMatrix &result) {
  //
  unsigned row = A.nrows();
  unsigned col = A.ncols();

  // TODO: Perform squareness checking.
  SymEngine::RCP<const SymEngine::Basic> t;
  SymEngine::vec_basic Av = A.as_vec_basic();
  SymEngine::vec_basic reflector;
  SymEngine::vec_basic tmp, uu;

  int i, j, k, c, idx, len;

  for(k = 0; k < row - 2; k++) {
    // Compute Householder reflector.
    len = col - (k + 1);
    reflector = SymEngine::vec_basic(len);

    for(i = k; i <= row - 2; i++) {
      reflector[i] = Av[(i + 1)*row + k + 1];
    }

    // Compute the norm.
    t = norm2(reflector);

    // u[1] = u[1] + sign(u[1]) * |u|
    reflector[0] = SymEngine::add(reflector[0],
                                  SymEngine::mul(SymEngine::sign(reflector[0]),
                                                 t));

    // u = u/|u|
    normalize(reflector);

    // Form u*u'
    uu = SymEngine::vec_basic(pow(reflector.size(), 2));
    for(i = 0; i < len; i++) { // row
      for(j = 0; j < len; j++) { // col
        uu[i*len + j] = SymEngine::mul(reflector[i], reflector[j]);
      }
    }

    // A_b = A_b - 2*u*u'*A_b
    tmp = SymEngine::vec_basic((row - (k + 1))*(col));
    idx = 0;
    for(i = k + 1; i < row; i++) { // row
      for(j = 0; j < col; j++) { // col

        tmp[idx] = SymEngine::zero;

        // Matrix multiplication.
        for(c = 0; c < len; c++) {
          tmp[idx] = SymEngine::add(tmp[idx],
                                    SymEngine::mul(uu[(i - (k + 1))*len + c],
                                                   Av[c*col + j]));
        }


        Av[i*col + j] = SymEngine::sub(Av[i*col + j],
                                       SymEngine::mul(SymEngine::integer(2),
                                                      tmp[idx]));

        idx++;
      }
    }

    auto d = SymEngine::DenseMatrix(row, col, {Av});
    printf("Av'\n%s\n", d.__str__().c_str());

    // t = norm2(reflector);
    //
    // printf("reflector norm %s\n", t->__str__().c_str());
    //
    // for(j = 0; j < reflector.size(); j++) {
    //   reflector[j] = SymEngine::div(reflector[i], t);
    //
    //   printf("reflector %d %s\n", j, reflector[j]->__str__().c_str());
    // }

    // printf("dims: [r: %d, c: %d]\n", col - (i + 2), i);

    // reflector = SymEngine::DenseMatrix(n - i - 2, 1);
    // result.submatrix(reflector, i + 1, i, n, i, 1, 1);
    //
    // printf("reflector\n%s\n", reflector.__str__().c_str());
  }

  // result = SymEngine::DenseMatrix(row, cols, {tmp});
}

} // Controls
