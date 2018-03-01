function sys = subs(sys, varargin)
%SUBS Replace a symbolic variable in state space.
%   Detailed explanation goes here

% p = inputParser;
% validateSys = @(sys) isa(sys, 'symss');
% addRequired(p, 'sys', validateSys);
% 
% parse(p, sys, varargin{:});

states = sys.states;
inputs = sys.inputs;
sys.states = subs(sys.states, sys.states, varargin);
sys.inputs = subs(sys.inputs, sys.inputs, varargin);
sys.f = subs(sys.f, [states; inputs], varargin);
sys.g = subs(sys.g, [states; inputs], varargin);

end
