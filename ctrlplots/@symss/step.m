function y = step(sys, varargin)
%STEP Compute the step response of a system.
%   y = STEP(sys)

p = inputParser;
validateSys = @(S) islinear(S.f, S.states);
addRequired(p, 'sys', validateSys);
parse(p, sys);

syms s
u = 1/s;

if nargout == 0
    lsim(sys, u, varargin{:});
else
    y = lsim(sys, u, varargin{:});
end

end

