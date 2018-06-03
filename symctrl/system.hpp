#ifndef SYMCTRL_SYSTEM_HPP
#define SYMCTRL_SYSTEM_HPP

#include <symengine/basic.h>

#include "control_model.hpp"
#include "visitor.hpp"

namespace Controls {

class System : public ControlModel {
public:
  virtual ~System() {};

  // Visitor Pattern
  virtual void accept(SystemVisitor &visitor) = 0;

  virtual void subs(const SymEngine::RCP<const SymEngine::Basic> key,
                    const SymEngine::RCP<const SymEngine::Basic> map) = 0;
};

} // Controls

#endif /* end of include guard: SYMCTRL_SYSTEM_HPP */
