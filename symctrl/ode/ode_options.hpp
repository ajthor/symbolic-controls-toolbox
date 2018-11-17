#ifndef SYMCTRL_ODE_ODE_OPTIONS_HPP
#define SYMCTRL_ODE_ODE_OPTIONS_HPP

namespace Controls {

// ----------------------------------------------------------------------
// ODE Options
//
class OdeOptions {
private:
  double step_size_;

public:
  OdeOptions(double step_size = 0.001);
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

OdeOptions::OdeOptions(double step_size) :
                       step_size_(step_size)
                       {}

} // Controls

#endif /* end of include guard: SYMCTRL_ODE_ODE_OPTIONS_HPP */
