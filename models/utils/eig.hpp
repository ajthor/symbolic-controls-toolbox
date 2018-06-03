#ifndef MODELS_UTILS_EIG_HPP
#define MODELS_UTILS_EIG_HPP

namespace Controls {

void compute_eigenvalues(SymEngine::DenseMatrix &A,
                         SymEngine::vec_basic &l,
                         SymEngine::vec_basic &v);

void compute_hessenberg(SymEngine::DenseMatrix &A,
                        SymEngine::DenseMatrix &result);

} // Controls

#endif /* end of include guard: MODELS_UTILS_EIG_HPP */
