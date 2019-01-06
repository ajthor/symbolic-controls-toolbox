#ifndef SYMCTRL_ODE_EULER_EULER_HPP
#define SYMCTRL_ODE_EULER_EULER_HPP

#include <symctrl/systems/system.hpp>
#include <symctrl/systems/statespace/statespace.hpp>
#include <symctrl/systems/visitor.hpp>
#include <symctrl/ode/options/options.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// EulerVisitor
//
class EulerVisitor : public SystemVisitor<EulerVisitor> {
private:
  std::vector<double> x0_;

  std::vector<double> &t_result_;
  std::vector<double> &x_result_;

  ode_options options_;

public:
  EulerVisitor(std::vector<double> x0,
               std::vector<double> &t_result,
               std::vector<double> &x_result,
               ode_options options);

  void visit(StateSpace &sys);

  template<typename DT>
  void visit(System<DT> &sys) {}
};

// ----------------------------------------------------------------------
// EulerVisitor Constructor
//
EulerVisitor::EulerVisitor(std::vector<double> x0,
                           std::vector<double> &t_result,
                           std::vector<double> &x_result,
                           ode_options options) :
                           x0_(x0),
                           t_result_(t_result),
                           x_result_(x_result),
                           options_(options) {
  //
}

// ----------------------------------------------------------------------
// ode_euler
//
void ode_euler(StateSpace &sys,
               std::vector<double> x0,
               std::vector<double> &t_result,
               std::vector<double> &x_result);
//
void ode_euler(StateSpace &sys,
               std::vector<double> x0,
               std::vector<double> &t_result,
               std::vector<double> &x_result,
               ode_options options);

} // Controls

#endif // SYMCTRL_ODE_EULER_EULER_HPP
