function y = initial(sys, varargin)
%INITIAL Compute the zero state response of a system.
%   y = INITIAL(sys)
%   y = INITIAL(sys, x0)

p = inputParser;
validateSys = @(S) islinear(S.f, S.states);
addRequired(p, 'sys', validateSys);
parse(p, sys);

u = sym(0);

if nargout == 0
    lsim(sys, u, varargin{:});
else
    y = lsim(sys, u, varargin{:});
end

end

