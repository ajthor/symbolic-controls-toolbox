function u = slidectrl(sys, S, varargin)
%SLIDECTRL Computes an equivalent control input for sliding mode control.
%   Detailed explanation goes here

p = inputParser;
addRequired(p, 'sys');
addRequired(p, 'S');
addParameter(p, 'SwitchingFunction', @sign);
parse(p, sys, S, varargin{:});

sf = p.Results.SwitchingFunction;

sigma = S*sys.states;

[A, B, ~, ~] = getabcd(sys);
ueq = -(S*B)\S*A*sys.states;

eta = 1;

us = eta*(S*B)\sf(sigma);

u = ueq - us;

end

