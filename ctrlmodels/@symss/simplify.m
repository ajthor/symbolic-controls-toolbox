function sys = simplify(sys, varargin)
%SIMPLIFY Simplify a state space model.
%
%   sys = SIMPLIFY(sys, ...)
%   simplifies the state and output equations for a state space model.
%   Extra parameters are passed to the internal sym/simplify calls.
%   
%   Used to apply assumptions defined in the workspace to a state space
%   model.
% 
%   See also sym/simplify

sys.f = simplify(sys.f, varargin{:});
sys.g = simplify(sys.g, varargin{:});

end
