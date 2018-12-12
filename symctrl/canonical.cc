#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

#include "analysis.hpp"
#include "canonical.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Controllable Canonical Form
//
void ControllableFormVisitor::visit(StateSpace &m) {
  SymEngine::DenseMatrix A = m.get_A_matrix(),
                         B = m.get_B_matrix(),
                         C = m.get_C_matrix(),
                         D = m.get_D_matrix();

  SymEngine::DenseMatrix Co = SymEngine::DenseMatrix(1, 1,
                              {SymEngine::integer(1)});

  SymEngine::DenseMatrix Ci = SymEngine::DenseMatrix(1, 1,
                              {SymEngine::integer(1)});

  size_t n = m.get_num_states();

  // Get the number of inputs from the B matrix size.
  size_t m = B.ncols();

  // Compute the controllability matrix.
  ctrb(A, B, Co);

  // Single-input case (m = 1)
  if(m == 1) {
    Co.inv(Ci);

  // Multiple-input case (m > 1)
  } else {
    /* code */
  }

  // Compute new form.
  // size_t i;
  //
  // // f = A*x + B*u
  // M = SymEngine::DenseMatrix(n, 1);
  // R = SymEngine::DenseMatrix(n, 1);
  // A.mul_matrix(x, M);
  // B.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // fv = M.as_vec_basic();
  // for(i = 0; i < fv.size(); i++) {
  //   obj.set_f(i, fv[i]);
  // }
  //
  // // g = C*x + D*u
  // M = SymEngine::DenseMatrix(p, 1);
  // R = SymEngine::DenseMatrix(p, 1);
  // C.mul_matrix(x, M);
  // D.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // gv = M.as_vec_basic();
  // for(i = 0; i < gv.size(); i++) {
  //   obj.set_g(i, gv[i]);
  // }
}

// ----------------------------------------------------------------------
// Observable Canonical Form
//
void ObservableFormVisitor::visit(StateSpace &m) {
  // Compute new form.
  // size_t i;
  //
  // // f = A*x + B*u
  // M = SymEngine::DenseMatrix(n, 1);
  // R = SymEngine::DenseMatrix(n, 1);
  // A.mul_matrix(x, M);
  // B.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // fv = M.as_vec_basic();
  // for(i = 0; i < fv.size(); i++) {
  //   obj.set_f(i, fv[i]);
  // }
  //
  // // g = C*x + D*u
  // M = SymEngine::DenseMatrix(p, 1);
  // R = SymEngine::DenseMatrix(p, 1);
  // C.mul_matrix(x, M);
  // D.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // gv = M.as_vec_basic();
  // for(i = 0; i < gv.size(); i++) {
  //   obj.set_g(i, gv[i]);
  // }
}

// ----------------------------------------------------------------------
// Jordan Canonical Form
//
void JordanFormVisitor::visit(StateSpace &m) {
  // Compute new form.
  // size_t i;
  //
  // // f = A*x + B*u
  // M = SymEngine::DenseMatrix(n, 1);
  // R = SymEngine::DenseMatrix(n, 1);
  // A.mul_matrix(x, M);
  // B.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // fv = M.as_vec_basic();
  // for(i = 0; i < fv.size(); i++) {
  //   obj.set_f(i, fv[i]);
  // }
  //
  // // g = C*x + D*u
  // M = SymEngine::DenseMatrix(p, 1);
  // R = SymEngine::DenseMatrix(p, 1);
  // C.mul_matrix(x, M);
  // D.mul_matrix(u, R);
  // M.add_matrix(R, M);
  // gv = M.as_vec_basic();
  // for(i = 0; i < gv.size(); i++) {
  //   obj.set_g(i, gv[i]);
  // }
}

} // Controls
