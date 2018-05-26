#ifndef CONTROL_MATLAB_MATLAB_WRAPPER_HPP
#define CONTROL_MATLAB_MATLAB_WRAPPER_HPP

#ifdef __cplusplus
extern "C" {
#endif

int say_hello();

// #include "mex.hpp"
// #include "mexAdapter.hpp"
//
// using namespace matlab::data;
// using matlab::mex::ArgumentList;
// using matlab::engine::convertUTF8StringToUTF16String;
//
// template<class T>
// class MexFunction : public matlab::mex::Function {
// public:
//   MexFunction() {
//
//     mexLock();
//   }
//
//   ~MexFunction() {
//     delete cppObject;
//     mexUnlock();
//   }
//
//   void operator()(ArgumentList outputs, ArgumentList inputs);
//
//   void checkArguments(ArgumentList outputs, ArgumentList inputs);
//
// private:
//   std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
//
//   ArrayFactory factory;
// };

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: CONTROL_MATLAB_MATLAB_WRAPPER_HPP */
