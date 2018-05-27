#ifndef MODELS_TRANSFER_FUNCTION_HPP
#define MODELS_TRANSFER_FUNCTION_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/symbol.h>
#include <symengine/matrix.h>

#include "system.hpp"

namespace Controls {

class TransferFunction : public Controls::System {
public:
  TransferFunction();
  ~TransferFunction();

  void set_num(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg);
  void set_den(const std::vector<SymEngine::RCP<const SymEngine::Basic>> &arg);

  // void add_num(SymEngine::RCP<const SymEngine::Basic> arg);
  // void add_den(SymEngine::RCP<const SymEngine::Basic> arg);

  std::vector<SymEngine::RCP<const SymEngine::Basic>> get_num();
  std::vector<SymEngine::RCP<const SymEngine::Basic>> get_den();

private:
  std::vector<SymEngine::RCP<const SymEngine::Basic>> num_;
  std::vector<SymEngine::RCP<const SymEngine::Basic>> den_;
};

} // Controls

#endif /* end of include guard: MODELS_TRANSFER_FUNCTION_HPP */
