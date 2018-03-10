function phi = expm(sys)
%EXPM Compute the matrix exponential of a symbolic state space system.
% 
%   phi = EXPM(sys) computes the matrix exponential L^-1{(sI-A)^-1}.
% 
%   The standard 'expm' function computes the matrix exponential using a
%   convergent power series method. While this method is formally defined
%   as the matrix exponential, in practice the computation of this matrix
%   can cause Matlab to hang. Symbolically, it is easier to compute the
%   inverse laplace transform of (sI-A)^-1, and less error-prone.
p = inputParser;
validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);
parse(p, sys);

syms s t
Phi = inv(s*eye(size(sys.A)) - sys.A);
phi = ilaplace(Phi, s, t);

end
