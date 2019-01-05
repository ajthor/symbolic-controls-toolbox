#ifndef SYMCTRL_STATE_SPACE_HPP
#define SYMCTRL_STATE_SPACE_HPP

#include <algorithm>
#include <initializer_list>
#include <vector>

#include <symctrl/system.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/math/matrix/vector.hpp>
#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// StateSpace
//
class StateSpace : public System<StateSpace> {
public:
  explicit inline StateSpace();
  explicit inline StateSpace(std::initializer_list<symbolic_t> x,
                             std::initializer_list<symbolic_t> u,
                             std::initializer_list<symbolic_t> f,
                             std::initializer_list<symbolic_t> g);
  explicit inline StateSpace(const std::vector<symbolic_t> &x,
                             const std::vector<symbolic_t> &u,
                             const std::vector<symbolic_t> &f,
                             const std::vector<symbolic_t> &g);
  explicit inline StateSpace(const Math::SymbolicVector &x,
                             const Math::SymbolicVector &u,
                             const Math::SymbolicVector &f,
                             const Math::SymbolicVector &g);
  // explicit inline StateSpace(const Math::SymbolicDense &A,
  //                            const Math::SymbolicDense &B,
  //                            const Math::SymbolicDense &C,
  //                            const Math::SymbolicDense &D);

  inline StateSpace(const StateSpace &m);

  inline StateSpace &operator=(const StateSpace &m);

private:
  // Using a private nested class allows implementation details to be
  // abstracted from the public member variables.
  class ExpressionVector : public Math::SymbolicVector {
  public:
    using Math::SymbolicVector::SymbolicVector;
    using Math::SymbolicVector::operator=;
  };

public:
  // Vector of symbolic state variables.
  ExpressionVector state_variables;

  // Vector of symbolic input variables.
  ExpressionVector input_variables;

  // Vector of state equations.
  ExpressionVector state_equations;

  // Vector of output equations.
  ExpressionVector output_equations;

  // System matrices.
  Math::SymbolicDense A() const;
  Math::SymbolicDense B() const;
  Math::SymbolicDense C() const;
  Math::SymbolicDense D() const;

  void accept(Visitor &visitor);
};

// ----------------------------------------------------------------------
// StateSpace Constructor
//
inline StateSpace::StateSpace() {
  //
}

inline StateSpace::StateSpace(std::initializer_list<symbolic_t> x,
                              std::initializer_list<symbolic_t> u,
                              std::initializer_list<symbolic_t> f,
                              std::initializer_list<symbolic_t> g) {
  //
  state_variables = x;
  input_variables = u;
  state_equations = f;
  output_equations = g;
}

inline StateSpace::StateSpace(const std::vector<symbolic_t> &x,
                              const std::vector<symbolic_t> &u,
                              const std::vector<symbolic_t> &f,
                              const std::vector<symbolic_t> &g) :
                              state_variables(x),
                              input_variables(u),
                              state_equations(f),
                              output_equations(g) {
  //
  SYMCTRL_ASSERT(state_variables.size() == state_equations.size());
}

inline StateSpace::StateSpace(const Math::SymbolicVector &x,
                              const Math::SymbolicVector &u,
                              const Math::SymbolicVector &f,
                              const Math::SymbolicVector &g) :
                              state_variables(x),
                              input_variables(u),
                              state_equations(f),
                              output_equations(g) {
  //
  SYMCTRL_ASSERT(state_variables.size() == state_equations.size());
}

// inline StateSpace(const Math::SymbolicDense &A,
//                   const Math::SymbolicDense &B,
//                   const Math::SymbolicDense &C,
//                   const Math::SymbolicDense &D) {
//   //
// }

inline StateSpace::StateSpace(const StateSpace &m) {
  //
  state_variables = m.state_variables;
  input_variables = m.input_variables;
  state_equations = m.state_equations;
  output_equations = m.output_equations;
}

// ----------------------------------------------------------------------
// StateSpace Assignment Operator
//
inline StateSpace &StateSpace::operator=(const StateSpace &rhs) {
  state_variables = rhs.state_variables;
  input_variables = rhs.input_variables;
  state_equations = rhs.state_equations;
  output_equations = rhs.output_equations;

  return *this;
}

// ----------------------------------------------------------------------
// StateSpace Matrices
//
Math::SymbolicDense state_matrix(const StateSpace &sys);
Math::SymbolicDense input_matrix(const StateSpace &sys);
Math::SymbolicDense output_matrix(const StateSpace &sys);
Math::SymbolicDense feedforward_matrix(const StateSpace &sys);

const auto A_matrix = state_matrix;
const auto B_matrix = input_matrix;
const auto C_matrix = output_matrix;
const auto D_matrix = feedforward_matrix;

const auto system_matrix = state_matrix;
const auto feedthrough_matrix = feedforward_matrix;


bool check_abcd(SymEngine::MatrixBase &A,
                SymEngine::MatrixBase &B,
                SymEngine::MatrixBase &C,
                SymEngine::MatrixBase &D);

void set_abcd(StateSpace &obj,
              SymEngine::DenseMatrix &A,
              SymEngine::DenseMatrix &B,
              SymEngine::DenseMatrix &C,
              SymEngine::DenseMatrix &D);

// Separate dx/dt = f(.) + g(.)u into f(.) and g(.) terms.
void nonlinear_sep();

void c2d();
void d2c();

void similarity_transform(StateSpace &obj, SymEngine::DenseMatrix &P);

// ----------------------------------------------------------------------
// Linearization
//
StateSpace linearize(const StateSpace &obj);
// void linearize(const SymEngine::vec_basic &eq);

} // Controls

#endif // SYMCTRL_STATE_SPACE_HPP
