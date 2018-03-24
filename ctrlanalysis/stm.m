function Phi = stm(sys)
%STM Compute the state transition matrix of a system.
%   
%   Compute the state transition matrix defined by:
%       Phi = (sI - A)^-1
%   
%   Phi = STM(sys) computes the state transition matrix of a system.
%   
%   Phi = STM(A) computes the state transition matrix for a square state
%   matrix A.

p = inputParser;
validateSys = @(S) validateattributes(S, {'sym', 'symss'}, {'nonempty'});
addRequired(p, 'sys', validateSys);
parse(p, sys);

if isa(sys, 'symss')
    A = sys.A;
else
    A = sys;
end

syms s
Phi = inv(s*eye(size(A), 'like', A) - A);
    
end

