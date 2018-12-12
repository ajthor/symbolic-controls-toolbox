#include <tuple>
#include <vector>

// #include <symengine/basic.h>
// #include <symengine/dict.h>
#include <symengine/lambda_double.h>
#include <symengine/visitor.h>

#include "ode.hpp"

#include <symctrl/random_variable.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// Euler Method
//
class EulerVisitor : public SystemVisitor {
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
    size_t i, j, n = m.get_num_f();

    std::vector<SymEngine::LambdaRealDoubleVisitor> v(n);

    SymEngine::RCP<const SymEngine::Symbol> t = SymEngine::symbol("t");
    SymEngine::vec_basic fun_params;

    SymEngine::vec_basic funs;

    fun_params.push_back(t);

    // Initialize the RNG.
    std::random_device gen;

    SymEngine::vec_basic args;
    SymEngine::vec_basic rv_vec;

    for(i = 0; i < n; i++) {
      fun_params.push_back(m.get_state(i));
      funs.push_back(m.get_f(i));

      // Check if the function has random variables.
      // rv_vec.clear();
      // rv_vec = SymEngine::free_symbols(*m.get_f(i));
      args = m.get_f(i)->get_args();
      // for(j = 0; j < args.size(); j++) {
      //   if(is_a_random_variable(*args[j])) {
      //     // auto var = SymEngine::rcp_dynamic_cast<const RandomVariable>(args[j]);
      //     // std::cout << var->sample(gen) << '\n';
      //     // rv_vec.push_back(SymEngine::rcp_dynamic_cast<const RandomVariable>(args[j]));
      //   }
      // }
      if(!args.empty()) {
        for (auto it = args.begin(); it != args.end(); ++it) {
          // std::cout << *it << std::endl;
          if(is_a_random_variable(**it)) {
            // auto var = dynamic_cast<const RandomVariable*>(*it);
            // std::cout << (var)->sample(gen) << '\n';
            // rv_vec.push_back(dynamic_cast<const RandomVariable*>(it));
            rv_vec.push_back(*it);
          }
        }
      }
    }

    // std::cout << rv_vec << '\n';
    // if(rv_vec.size() > 0)
    //   std::cout << rv_vec[0]->sample(gen) << '\n';

    // Check if there are any RVs in the functions.
    if(rv_vec.size() > 0) {
      // Add the RVs to the variables list.
      for (auto it = rv_vec.begin(); it != rv_vec.end(); ++it) {
        fun_params.push_back(*it);
      }
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

    auto pos = current_val.begin();
    auto rv_pos = current_val.end();

    double d;

    // Main ODE loop.
    do {
      // Get the current n values.
      current_val = last_val;

      pos = current_val.begin();
      pos = current_val.insert(pos, t_current);

      if(rv_vec.size() > 0) {
        rv_pos = current_val.end();
        for (auto it = rv_vec.begin(); it != rv_vec.end(); ++it) {
          rv_pos = current_val.insert(rv_pos, SymEngine::rcp_dynamic_cast<const RandomVariable>(*it)->sample(gen));
        }
      }

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

  virtual void visit(System &m) {}
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
