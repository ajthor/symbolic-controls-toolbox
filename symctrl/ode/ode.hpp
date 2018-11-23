#ifndef SYMCTRL_ODE_ODE_HPP
#define SYMCTRL_ODE_ODE_HPP

#include <symctrl/visitor.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// ODE Options
//
class OdeOptions {
private:
  double step_size_;

public:
  OdeOptions(double step_size = 0.001) : step_size_(step_size) {}
  ~OdeOptions() {}

  void set_step_size(double step_size) {
    if(step_size <= 0) {
      // TODO: Add error checking.
      return;
    }
    step_size_ = step_size;
  }
  double get_step_size() const { return step_size_; }
};

// ----------------------------------------------------------------------
// ODE Euler Solver
//
void ode_euler(StateSpace &m,
               std::vector<double> &t_span,
               std::vector<double> &x0,
               std::vector<double> &t_result,
               std::vector<double> &x_result,
               OdeOptions &options);

} // Controls

#endif /* end of include guard: SYMCTRL_ODE_ODE_HPP */
