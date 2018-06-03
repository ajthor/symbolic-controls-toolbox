#ifndef MODELS_SYSTEM_HPP
#define MODELS_SYSTEM_HPP

#include "control_model.hpp"

namespace Controls {

class System : public Controls::ControlModel {
public:
  virtual ~System() {};

  virtual void subs(const SymEngine::RCP<const SymEngine::Basic> key,
                    const SymEngine::RCP<const SymEngine::Basic> map) = 0;
};

} // Controls

#endif /* end of include guard: MODELS_SYSTEM_HPP */
