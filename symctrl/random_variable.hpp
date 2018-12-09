#ifndef SYMCTRL_RANDOM_VARIABLE_HPP
#define SYMCTRL_RANDOM_VARIABLE_HPP

#include <symengine/symbol.h>

#include "random_distribution.hpp"

using SymEngine::Basic;
using SymEngine::make_rcp;
using SymEngine::RCP;
using SymEngine::Symbol;

namespace Controls {

// ----------------------------------------------------------------------
// RandomVariable
//
class RandomVariable : public Symbol {
private:
  RandomNumberDistribution *dist_;

public:
  explicit RandomVariable(const RCP<const Symbol> &s,
                          RandomNumberDistribution *dist) :
                          Symbol(s->get_name()),
                          dist_(dist) {}
  explicit RandomVariable(const std::string &name,
                          RandomNumberDistribution *dist) :
                          Symbol(name),
                          dist_(dist) {}

  double sample(std::random_device &gen) const {
    return sample_distribution(*dist_, gen);
  }
};

inline RCP<const RandomVariable>
random_variable(const std::string &name,
                RandomNumberDistribution *dist) {
    return make_rcp<const RandomVariable>(name, dist);
}

// ----------------------------------------------------------------------
// Utility Functions
//
inline bool is_a_random_variable(const SymEngine::Basic &b) {
    return dynamic_cast<const RandomVariable*>(&b) != nullptr;
}

} // Controls

#endif /* end of include guard: SYMCTRL_RANDOM_VARIABLE_HPP */
