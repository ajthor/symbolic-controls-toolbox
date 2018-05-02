function T = subs(G, varargin)
%SUBS Replace a symbolic variable in state space.
%
%   sys = SUBS(sys, ...) utility wrapper for 'subs' function.

T = copy(G);
T.Numerator = subs(T.Numerator, varargin{:});
T.Denominator = subs(T.Denominator, varargin{:});

end
