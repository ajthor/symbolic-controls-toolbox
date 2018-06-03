#ifndef SYMCTRL_HYBRID_SYSTEM_HPP
#define SYMCTRL_HYBRID_SYSTEM_HPP

#include <vector>
#include <symengine/basic.h>

#include "state_space.hpp"

namespace Controls {

class HybridSystem : public StateSpace {
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

#endif /* end of include guard: SYMCTRL_HYBRID_SYSTEM_HPP */
