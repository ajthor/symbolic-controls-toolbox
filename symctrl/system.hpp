#ifndef SYMCTRL_SYSTEM_HPP
#define SYMCTRL_SYSTEM_HPP

namespace Controls {

class Visitor;

// ----------------------------------------------------------------------
// System Class
//
class System {
public:
  virtual ~System() {};

  // Visitor Pattern
  virtual void accept(Visitor &visitor) = 0;
};

} // Controls

#endif /* end of include guard: SYMCTRL_SYSTEM_HPP */
