#ifndef SYMCTRL_SYSTEMS_TRANSFERFUNCTION_TRANSFERMATRIX_HPP
#define SYMCTRL_SYSTEMS_TRANSFERFUNCTION_TRANSFERMATRIX_HPP

#include <utility>
#include <vector>

#include <symengine/basic.h>
#include <symengine/mul.h>
#include <symengine/symbol.h>

#include <symctrl/systems/system.hpp>
#include <symctrl/systems/transferfunction/transferfunction.hpp>
#include <symctrl/math/matrix/dense.hpp>
#include <symctrl/shims/symbolic.hpp>

namespace Controls {

// ----------------------------------------------------------------------
// TransferMatrix
//
class TransferMatrix : public System<TransferMatrix>,
                       public DenseMatrix<TransferFunction> {
public:
  using DenseMatrix<TransferFunction>::DenseMatrix;
  using DenseMatrix<TransferFunction>::operator=;
};

} // Controls

#endif // SYMCTRL_SYSTEMS_TRANSFERFUNCTION_TRANSFERMATRIX_HPP