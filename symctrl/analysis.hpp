#ifndef SYMCTRL_ANALYSIS_HPP
#define SYMCTRL_ANALYSIS_HPP

#include <symengine/matrix.h>

#include "visitor.hpp"

using SymEngine::DenseMatrix;

namespace Controls {

// ----------------------------------------------------------------------
// Matrix Exponential
//
void expm(StateSpace &obj);

// ----------------------------------------------------------------------
// Controllability
//
void ctrb(StateSpace &obj, DenseMatrix &result);
void ctrb(DenseMatrix &A,
          DenseMatrix &B,
          DenseMatrix &result);

// TODO: Implement rank revealing function.
size_t ctrb_rank(StateSpace *obj);
size_t ctrb_rank(DenseMatrix &C);

bool is_controllable(DenseMatrix &Co);

// ----------------------------------------------------------------------
// Observability
//
void obsv(StateSpace &obj, DenseMatrix &result);
void obsv(DenseMatrix &A,
          DenseMatrix &C,
          DenseMatrix &result);

// TODO: Implement rank revealing function.
size_t obsv_rank(StateSpace *obj);
size_t obsv_rank(DenseMatrix &C);

bool is_observable(DenseMatrix &Ob);

} // Controls

#endif /* end of include guard: SYMCTRL_ANALYSIS_HPP */
