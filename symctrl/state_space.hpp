#ifndef SYMCTRL_STATE_SPACE_HPP
#define SYMCTRL_STATE_SPACE_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/matrix.h>

#include "system.hpp"

using SymEngine::Basic;
using SymEngine::DenseMatrix;
using SymEngine::MatrixBase;
using SymEngine::RCP;

namespace Controls {

// ----------------------------------------------------------------------
// StateSpace
//
class StateSpace : public System {
public:
  StateSpace();
  StateSpace(MatrixBase &A,
             MatrixBase &B,
             MatrixBase &C,
             MatrixBase &D);
  ~StateSpace();

  void add_state(const RCP<const Basic> arg);
  void set_state(const size_t n, const RCP<const Basic> arg);
  RCP<const Basic> get_state(const size_t n) const;
  // void remove_state(const size_t n);
  size_t get_num_states() const;

  void add_input(const RCP<const Basic> arg);
  void set_input(const size_t n, const RCP<const Basic> arg);
  RCP<const Basic> get_input(const size_t n) const;
  // void remove_input(const size_t n);
  size_t get_num_inputs() const;

  void add_f(const RCP<const Basic> arg);
  void set_f(const size_t n, const RCP<const Basic> arg);
  RCP<const Basic> get_f(const size_t n) const;
  // void remove_f(const size_t n);
  size_t get_num_f() const;

  void add_g(const RCP<const Basic> arg);
  void set_g(const size_t n, const RCP<const Basic> arg);
  RCP<const Basic> get_g(const size_t n) const;
  // void remove_g(const size_t n);
  size_t get_num_g() const;

  void get_A_matrix(DenseMatrix &result) const;
  void get_B_matrix(DenseMatrix &result) const;
  void get_C_matrix(DenseMatrix &result) const;
  void get_D_matrix(DenseMatrix &result) const;

  void accept(Visitor &visitor);

protected:
  // Vector of symbolic state variables.
  SymEngine::vec_basic states_;

  // Vector of symbolic input variables.
  SymEngine::vec_basic inputs_;

  // Vector of state equations.
  SymEngine::vec_basic f_;

  // Vector of output equations.
  SymEngine::vec_basic g_;

  // TODO: Add sparse matrix backend to state space class.
  // SymEngine::CSRMatrix A;
  // SymEngine::CSRMatrix B;
  // SymEngine::CSRMatrix C;
  // SymEngine::CSRMatrix D;
};


bool check_abcd(MatrixBase &A,
                MatrixBase &B,
                MatrixBase &C,
                MatrixBase &D);

void set_abcd(StateSpace &obj,
              DenseMatrix &A,
              DenseMatrix &B,
              DenseMatrix &C,
              DenseMatrix &D);

// Separate dx/dt = f(.) + g(.)u into f(.) and g(.) terms.
void nonlinear_sep();

void c2d();
void d2c();

void similarity_transform(StateSpace &obj, DenseMatrix &P);

// ----------------------------------------------------------------------
// Linearization
//
void linearize(StateSpace &obj);
// void linearize(const SymEngine::vec_basic &eq);

} // Controls

#endif /* end of include guard: SYMCTRL_STATE_SPACE_HPP */
