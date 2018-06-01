#ifndef MODELS_ANALYSIS_HPP
#define MODELS_ANALYSIS_HPP

#include <symengine/basic.h>
#include <symengine/matrix.h>

#include "state_space.hpp"

namespace Controls {

// StateSpace Functions
void ctrb(StateSpace &obj, SymEngine::DenseMatrix &result);
void ctrb(SymEngine::DenseMatrix &A,
          SymEngine::DenseMatrix &B,
          SymEngine::DenseMatrix &result);

int ctrb_rank(StateSpace *obj);

bool is_controllable(SymEngine::DenseMatrix &Co);

void obsv(StateSpace &obj, SymEngine::DenseMatrix &result);
void obsv(SymEngine::DenseMatrix &A,
          SymEngine::DenseMatrix &C,
          SymEngine::DenseMatrix &result);

int obsv_rank(StateSpace *obj);

bool is_observable(SymEngine::DenseMatrix &Ob);

} // Controls

#endif /* end of include guard: MODELS_ANALYSIS_HPP */
