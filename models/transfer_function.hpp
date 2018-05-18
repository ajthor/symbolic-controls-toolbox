#ifndef MODELS_TRANSFER_FUNCTION_HPP
#define MODELS_TRANSFER_FUNCTION_HPP

#include <vector>
#include <symengine/basic.h>
#include <symengine/dict.h>
#include <symengine/symbol.h>
#include <symengine/matrix.h>

#include "system.hpp"

using SymEngine::Basic;
using SymEngine::DenseMatrix;
using SymEngine::Symbol;
using SymEngine::RCP;

namespace Controls {

class TransferFunction : public System {
public:
  TransferFunction();
  ~TransferFunction();

  void set_num(const std::vector<RCP<const Basic>> &arg);
  void set_den(const std::vector<RCP<const Basic>> &arg);

  // void add_num(RCP<const Basic> arg);
  // void add_den(RCP<const Basic> arg);

  std::vector<RCP<const Basic>> get_num();
  std::vector<RCP<const Basic>> get_den();

private:
  std::vector<RCP<const Basic>> num_;
  std::vector<RCP<const Basic>> den_;
};

} // Controls

#endif /* end of include guard: MODELS_TRANSFER_FUNCTION_HPP */
