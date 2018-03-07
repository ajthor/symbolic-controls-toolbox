function Phi = stm(varargin)
%STM Compute the state transition matrix of a system.
%   
%   Compute the state transition matrix defined by:
%       Phi = (sI - A)^-1
%   
%   Phi = STM(sys) computes the state transition matrix of a system.
%   
%   Phi = STM(A) computes the state transition matrix for a square state
%   matrix A.
ni = nargin;
if ni == 1
    if isa(varargin{1}, 'symss')
        A = varargin{1}.A;
    else
        A = varargin{1};
    end
else
    error('Wrong number of arguments.');
end

syms s
Phi = inv(s*eye(size(A), 'like', A) - A);
    
end

