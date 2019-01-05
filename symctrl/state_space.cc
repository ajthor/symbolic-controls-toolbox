#include <vector>

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/subs.h>

#include <symctrl/state_space.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/vector.hpp>
#include <symctrl/math/matrix/expression.hpp>
#include <symctrl/math/matrix/operation/jacobian.hpp>
#include <symctrl/shims/symbolic.hpp>

using Controls::Math::SymbolicDense;
using Controls::Math::SymbolicVector;

namespace Controls {

// ----------------------------------------------------------------------
// State Matrix
//
SymbolicDense state_matrix(const StateSpace &sys) {
  return Math::jacobian(sys.state_equations, sys.state_variables);
}

// ----------------------------------------------------------------------
// Input Matrix
//
SymbolicDense input_matrix(const StateSpace &sys) {
  return Math::jacobian(sys.state_equations, sys.input_variables);
}

// ----------------------------------------------------------------------
// Output Matrix
//
SymbolicDense output_matrix(const StateSpace &sys) {
  return Math::jacobian(sys.output_equations, sys.state_variables);
}

// ----------------------------------------------------------------------
// Feed-forward Matrix
//
SymbolicDense feedforward_matrix(const StateSpace &sys) {
  return Math::jacobian(sys.output_equations, sys.input_variables);
}

// ----------------------------------------------------------------------
// StateSpace Member Function Definitions
//
SymbolicDense StateSpace::A() const {
  return state_matrix(*this);
}

SymbolicDense StateSpace::B() const {
  return input_matrix(*this);
}

SymbolicDense StateSpace::C() const {
  return output_matrix(*this);
}

SymbolicDense StateSpace::D() const {
  return feedforward_matrix(*this);
}

// bool check_abcd(const SymEngine::MatrixBase &A,
//                 const SymEngine::MatrixBase &B,
//                 const SymEngine::MatrixBase &C,
//                 const SymEngine::MatrixBase &D) {
//   //
//   size_t n = A.ncols();
//   size_t m = B.ncols();
//   size_t p = C.nrows();
//
//   // A = [n, n]
//   // B = [n, m]
//   // C = [p, n]
//   // D = [p, m]
//
//   return true;
// }
//
// void set_abcd(StateSpace &obj,
//               SymEngine::DenseMatrix &A,
//               SymEngine::DenseMatrix &B,
//               SymEngine::DenseMatrix &C,
//               SymEngine::DenseMatrix &D) {
//   //
//   size_t n = obj.get_num_states();
//   size_t m = obj.get_num_inputs();
//   size_t p = obj.get_num_g();
//   size_t i, j;
//
//   SymEngine::DenseMatrix x, u, M, R;
//   SymEngine::vec_basic fv, gv, xv, xu;
//
//   for(i = 0; i < n; i++) {
//     xv.push_back(obj.get_state(i));
//     // x.set(i, 1, obj.get_state(i));
//   }
//   x = SymEngine::DenseMatrix(n, 1, {xv});
//
//   for(i = 0; i < m; i++) {
//     xu.push_back(obj.get_input(i));
//     // u.set(i, 1, obj.get_input(i));
//   }
//   u = SymEngine::DenseMatrix(m, 1, {xu});
//
//   // f = A*x + B*u
//   M = SymEngine::DenseMatrix(n, 1);
//   R = SymEngine::DenseMatrix(n, 1);
//   A.mul_matrix(x, M);
//   B.mul_matrix(u, R);
//   M.add_matrix(R, M);
//   fv = M.as_vec_basic();
//   for(i = 0; i < fv.size(); i++) {
//     obj.set_f(i, fv[i]);
//   }
//
//   // g = C*x + D*u
//   M = SymEngine::DenseMatrix(p, 1);
//   R = SymEngine::DenseMatrix(p, 1);
//   C.mul_matrix(x, M);
//   D.mul_matrix(u, R);
//   M.add_matrix(R, M);
//   gv = M.as_vec_basic();
//   for(i = 0; i < gv.size(); i++) {
//     obj.set_g(i, gv[i]);
//   }
// }

// ----------------------------------------------------------------------
// Linearization
//
// Substitute x and u for 0 in A, B, C, D.
StateSpace linearize(const StateSpace &sys) {
  size_t n = sys.state_variables.size();
  size_t m = sys.input_variables.size();
  size_t p = sys.output_equations.size();

  SymEngine::map_basic_basic d;
  SymbolicDense A = sys.A();
  SymbolicDense B = sys.B();
  SymbolicDense C = sys.C();
  SymbolicDense D = sys.D();

  for(size_t i = 0; i < n; i++) {
    d[sys.state_variables[i]] = symbolic_zero();
  }

  for(size_t i = 0; i < m; i++) {
    d[sys.input_variables[i]] = symbolic_zero();
  }

  for(size_t i = 0; i < A.nrows(); i++) {
    for(size_t j = 0; j < A.ncols(); j++) {
      A(i, j) = SymEngine::ssubs(A(i, j), d);
    }
  }
  for(size_t i = 0; i < B.nrows(); i++) {
    for(size_t j = 0; j < B.ncols(); j++) {
      B(i, j) = SymEngine::ssubs(B(i, j), d);
    }
  }
  for(size_t i = 0; i < C.nrows(); i++) {
    for(size_t j = 0; j < C.ncols(); j++) {
      C(i, j) = SymEngine::ssubs(C(i, j), d);
    }
  }
  for(size_t i = 0; i < D.nrows(); i++) {
    for(size_t j = 0; j < D.ncols(); j++) {
      D(i, j) = SymEngine::ssubs(D(i, j), d);
    }
  }

  return StateSpace(sys.state_variables,
                    sys.input_variables,
                    A*sys.state_variables + B*sys.input_variables,
                    C*sys.state_variables + D*sys.input_variables);
}

} // Controls
