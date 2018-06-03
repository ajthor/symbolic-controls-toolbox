#ifndef MODELS_TRANSFER_FUNCTION_HPP
#define MODELS_TRANSFER_FUNCTION_HPP

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

  void subs(const SymEngine::RCP<const SymEngine::Basic> key,
            const SymEngine::RCP<const SymEngine::Basic> map);

private:
  std::vector<SymEngine::RCP<const SymEngine::Basic>> num_;
  std::vector<SymEngine::RCP<const SymEngine::Basic>> den_;
};

} // Controls

#endif /* end of include guard: MODELS_TRANSFER_FUNCTION_HPP */
