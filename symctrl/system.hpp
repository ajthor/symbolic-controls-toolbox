#ifndef SYMCTRL_SYSTEM_HPP
#define SYMCTRL_SYSTEM_HPP

namespace Controls {

class SystemVisitor;

class System {
public:
  virtual ~System() {};

  // Visitor Pattern
  virtual void accept(SystemVisitor &visitor) = 0;
};

} // Controls

#endif /* end of include guard: SYMCTRL_SYSTEM_HPP */
