function sys = subs(sys, varargin)
%SUBS Replace a symbolic variable in state space.
%   
%   sys = SUBS(sys, ...) utility wrapper for 'subs' function.
sys.Numerator = subs(sys.Numerator, varargin{:});
sys.Denominator = subs(sys.Denominator, varargin{:});

end

