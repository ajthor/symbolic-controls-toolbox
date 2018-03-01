function sys = subs(sys, varargin)
%SUBS Replace a symbolic variable in state space.
%   Detailed explanation goes here

% p = inputParser;
% validateSys = @(sys) isa(sys, 'symss');
% addRequired(p, 'sys', validateSys);
% 
% parse(p, sys, varargin{:});

if nargin == 2
    S = sys.states;
    I = sys.inputs;
    sys.states = subs(sys.states, [S; I], varargin);
    sys.inputs = subs(sys.inputs, [S; I], varargin);
    sys.f = subs(sys.f, [S; I], varargin);
    sys.g = subs(sys.g, [S; I], varargin);
elseif nargin > 2
    sys.states = subs(sys.states, varargin{:});
    sys.inputs = subs(sys.inputs, varargin{:});
    sys.f = subs(sys.f, varargin{:});
    sys.g = subs(sys.g, varargin{:});
else
    sys = simplify(sys);
end

end
