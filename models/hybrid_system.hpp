#ifndef MODELS_HYBRID_SYSTEM_HPP
#define MODELS_HYBRID_SYSTEM_HPP

#include "state_space.hpp"

namespace Controls {

class HybridSystem : public Controls::StateSpace {
public:
  HybridSystem();
  ~HybridSystem();

private:

};

} // Controls

#endif /* end of include guard: MODELS_HYBRID_SYSTEM_HPP */
