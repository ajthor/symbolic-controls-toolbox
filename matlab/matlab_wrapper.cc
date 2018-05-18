#include "matlab_wrapper.hpp"

// void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
//
// }

void operator()(ArgumentList outputs, ArgumentList inputs) {
 checkArguments(outputs, inputs);

 // outputs[0] =
}

void checkArguments(ArgumentList outputs, ArgumentList inputs) {

  if (outputs.size() > 1) {
    matlabPtr->feval(convertUTF8StringToUTF16String("error"),
      0,
      std::vector<Array>({factory.createScalar("Too many outputs.")}));
  }
}
