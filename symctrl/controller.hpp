#ifndef SYMCTRL_CONTROLLER_HPP
#define SYMCTRL_CONTROLLER_HPP

#include <vector>

#include <symengine/basic.h>
#include <symengine/dict.h>

#include "visitor.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Controller Class
//
class Controller : public SystemVisitor<Controller> {
public:
  virtual ~Controller() {}
  virtual void visit(System &s) = 0;
};

// ----------------------------------------------------------------------
// Gain Controller
//
class GainController : public Controller {
private:
  std::vector<double> *k_;
  SymEngine::vec_basic r_;

public:
  GainController(SymEngine::vec_basic r,
                 std::vector<double> *K) :
                 r_(r),
                 k_(K) {}
  ~GainController() {}

  void visit(StateSpace &s);
  void visit(System &s) {};
};

// ----------------------------------------------------------------------
// PID Controller
//
class PIDController : public Controller {
private:

public:
  PIDController() {}
  ~PIDController() {}

  void visit(StateSpace &s);
  void visit(System &s) {};
};

// ----------------------------------------------------------------------
// LQR Controller
//
class LQRController : public Controller {
private:

public:
  LQRController() {}
  ~LQRController() {}

  void visit(StateSpace &s);
  void visit(System &s) {};
};

// ----------------------------------------------------------------------
// DLQR Controller
//
class DLQRController : public Controller {
private:

public:
  DLQRController() {}
  ~DLQRController() {}

  void visit(StateSpace &s);
  void visit(System &s) {};
};

// ----------------------------------------------------------------------
// Lyapunov Controller
//
class LyapunovController : public Controller {
private:

public:
  LyapunovController() {}
  ~LyapunovController() {}

  void visit(StateSpace &s);
  void visit(System &s) {};
};

// ----------------------------------------------------------------------
// FeedbackLinearization Controller
//
class FeedbackLinearizationController : public Controller {
private:

public:
  FeedbackLinearizationController() {}
  ~FeedbackLinearizationController() {}

  void visit(StateSpace &s);
  void visit(System &s) {};
};

// ----------------------------------------------------------------------
// SlidingMode Controller
//
class SlidingModeController : public Controller {
private:

public:
  SlidingModeController() {}
  ~SlidingModeController() {}

  void visit(StateSpace &s);
  void visit(System &s) {};
};

// ----------------------------------------------------------------------
// MPC Controller
//
class MPCController : public Controller {
private:

public:
  MPCController() {}
  ~MPCController() {}

  void visit(StateSpace &s);
  void visit(System &s) {};
};

} // Controls

#endif /* end of include guard: SYMCTRL_CONTROLLER_HPP */
