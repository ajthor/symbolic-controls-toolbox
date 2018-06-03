#ifndef SYMCTRL_SYSTEM_HPP
#define SYMCTRL_SYSTEM_HPP

#include <symengine/basic.h>

#include "control_model.hpp"

namespace Controls {

class SystemVisitor;

class System : public ControlModel {
public:
  virtual ~System() {};


  virtual void subs(const SymEngine::RCP<const SymEngine::Basic> key,
                    const SymEngine::RCP<const SymEngine::Basic> map) = 0;

  // Visitor Pattern
  virtual void accept(SystemVisitor &visitor) = 0;
};

} // Controls

#endif /* end of include guard: SYMCTRL_SYSTEM_HPP */
