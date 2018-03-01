function sys = simplify(sys, varargin)
%SIMPLIFY Simplify a system using assumptions.
%
%   sys = SIMPLIFY(sys, ...)
%   
%   Simplifies the state and output equations for a state space model.
%   
%   Applies assumptions defined in the workspace to simplify a state space
%   system.
p = inputParser;
validateSys = @(sys) isa(sys, 'symss');
addRequired(p, 'sys', validateSys);
parse(p, sys, varargin{:});

% Apply the assumptions to the state matrices.
sys.f = simplify(sys.f, varargin{:});
sys.g = simplify(sys.g, varargin{:});

end
