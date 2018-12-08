#ifndef SYMCTRL_RANDOM_VARIABLE_HPP
#define SYMCTRL_RANDOM_VARIABLE_HPP

#include <symengine/symbol.h>

#include "random_distribution.hpp"

using SymEngine::Symbol;
using SymEngine::RCP;
using SymEngine::make_rcp;

namespace Controls {

// ----------------------------------------------------------------------
// RandomVariable
//
class RandomVariable : public Symbol {
private:
  // std::shared_ptr<RandomNumberDistribution> dist_;
  // std::unique_ptr<RandomNumberDistribution> dist_;
  RandomNumberDistribution *dist_;

public:
  explicit RandomVariable(const std::string &name) : Symbol(name) {}
  // explicit RandomVariable(const std::string &name);
  explicit RandomVariable(const std::string &name,
                          RandomNumberDistribution *dist) :
                          Symbol(name),
                          dist_(dist) {}

  // void set_name(const std::string name) { name_ = name; }
  // void set_distribution(RandomNumberDistribution *dist) { dist_ = dist; }

  // template<typename T>
  // double sample(const std::random_device *gen) const { return (dist_)(gen); };
  // double sample(const std::random_device *gen) const { return *dist_::operator()(gen); };
  double sample(std::random_device &gen) const {
    return sample_distribution(*dist_, gen);
  }
};

// RandomVariable::RandomVariable(const std::string &name) :
//                                Symbol(name) {}
// RandomVariable::RandomVariable(const std::string &name,
//                                RandomNumberDistribution *dist) :
//                                Symbol(name),
//                                dist_(dist) {}
// RandomVariable::RandomVariable(const std::string &name,
//                                RandomNumberDistribution *dist) :
//                                Symbol(name) {
//   //
//   // dist_ = std::make_shared<RandomNumberDistribution>(dist);
// }

// inline RCP<const RandomVariable>
// random_variable(const std::string &name, RandomNumberDistribution *dist);
inline RCP<const RandomVariable>
random_variable(const std::string &name,
                RandomNumberDistribution *dist) {
    return make_rcp<const RandomVariable>(name, dist);
}

// // template<typename T>
// double RandomVariable::sample(const std::random_device *gen) const {
//   return (*dist_)(gen);
//   // return (this->*dist_)(gen);
//   // return (this->dist_)->min();
// }

// ----------------------------------------------------------------------
// SampleVisitor
//

// ----------------------------------------------------------------------
// Utility Functions
//
inline SymEngine::RCP<const RandomVariable*> cast_basic_to_rv(const SymEngine::Basic &b);

inline bool is_a_random_variable(const SymEngine::Basic &b) {
    return dynamic_cast<const RandomVariable*>(&b) != nullptr;
}

} // Controls

#endif /* end of include guard: SYMCTRL_RANDOM_VARIABLE_HPP */
