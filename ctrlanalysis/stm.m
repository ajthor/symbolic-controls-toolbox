function Phi = stm(varargin)
%STM Compute the state transition matrix of a system.
% 
%   Phi = STM(sys)
%   Phi = STM(A)
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

