#include <tuple>
#include <vector>

#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/lambda_double.h>

#include "ode.hpp"

namespace Controls {

// ----------------------------------------------------------------------
// Euler Method
//
class EulerVisitor : public StateSpaceVisitor {
private:
  std::vector<double> &t_span_;

  std::vector<double> &x0_;

  std::vector<double> &t_result_;
  std::vector<double> &x_result_;

  OdeOptions &options_;

public:
  EulerVisitor(std::vector<double> &t_span,
              std::vector<double> &x0,
              std::vector<double> &t_result,
              std::vector<double> &x_result,
              OdeOptions &options) :
              t_span_(t_span),
              x0_(x0),
              t_result_(t_result),
              x_result_(x_result),
              options_(options) {}

  ~EulerVisitor() {}

  virtual void visit(StateSpace &m) {
    size_t i, n = m.get_num_f();

    std::vector<SymEngine::LambdaRealDoubleVisitor> v(n);

    SymEngine::RCP<const SymEngine::Symbol> t = SymEngine::symbol("t");
    SymEngine::vec_basic fun_params;

    SymEngine::vec_basic funs;

    fun_params.push_back(t);

    for(i = 0; i < n; i++) {
      fun_params.push_back(m.get_state(i));
      funs.push_back(m.get_f(i));
    }

    // Initialize Lambda functions.
    for(i = 0; i < n; i++) {
      v[i].init({fun_params}, *funs[i]);
    }

    double t_begin = t_span_.front();
    double t_end = t_span_.back();
    double t_current = t_begin;

    double dt = options_.get_step_size();

    for(i = 0; i < n; i++) {
      x_result_.push_back(x0_[i]);
    }

    t_result_.push_back(t_current);

    std::vector<double> current_val;
    std::vector<double> last_val;
    last_val = x_result_;

    double d;

    // Main ODE loop.
    do {
      // Get the current n values.
      current_val = last_val;

      auto pos = current_val.begin();
      pos = current_val.insert(pos, t_current);

      // Evaluate the state functions.
      for(i = 0; i < n; i++) {
        // Store the result in last_val.
        d = v[i].call(current_val);
        last_val[i] = last_val[i] + (dt*d);
        // Add the result to the result vector.
        x_result_.push_back(last_val[i]);
      }

      // Advance the time.
      t_current += dt;
      t_result_.push_back(t_current);

    } while(t_current <= t_end);
  }

  virtual void visit(TransferFunction &m) {}
};

void ode_euler(StateSpace &m,
               std::vector<double> &t_span,
               std::vector<double> &x0,
               std::vector<double> &t_result,
               std::vector<double> &x_result,
               OdeOptions &options) {
  //
  EulerVisitor v(t_span, x0, t_result, x_result, options);
  m.accept(v);
}

} // Controls
