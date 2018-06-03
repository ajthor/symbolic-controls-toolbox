#ifndef MODELS_HYBRID_SYSTEM_HPP
#define MODELS_HYBRID_SYSTEM_HPP

#include "state_space.hpp"

namespace Controls {

class HybridSystem : public Controls::StateSpace {
public:
  HybridSystem();
  ~HybridSystem();

private:
  std::vector<SymEngine::RCP<const SymEngine::Basic>> states_;
  std::vector<SymEngine::RCP<const SymEngine::Basic>> inputs_;
  std::vector<std::vector<SymEngine::RCP<const SymEngine::Basic>>> f_;
  std::vector<SymEngine::RCP<const SymEngine::Basic>> g_;
};

} // Controls

#endif /* end of include guard: MODELS_HYBRID_SYSTEM_HPP */
