function [t, y] = effort(sys, u, varargin)
%EFFORT Compute the control effort of a system to arbitrary inputs.
%   
%   [t, y] = EFFORT(sys, u, t) computes the control effort of a system.

T = sys;
T.f = T.B*T.inputs;

if nargout == 0
    nlsim(T, u, varargin{:});
else
    [t, y] = nlsim(T, u, varargin{:});
end

end

