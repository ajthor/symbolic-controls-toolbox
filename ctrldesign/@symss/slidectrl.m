function u = slidectrl(sys, S, varargin)
%SLIDECTRL Computes a control input for sliding mode control.
%   
%   u = SLIDECTRL(sys, S, ...) computes a control input for sliding mode
%   control using a matrix defining the sliding surfaces S. The total
%   control is defined by the equation:
% 
%   u = ueq - us
% 
%   Where the equivalent control 'ueq' is defined by:
%              -1
%   ueq = -(SB)  SAx
% 
%   and the surface control is defined by:
%                -1
%   us = eta*(SB)  sign(sigma)
% 
%   The switching function, which defaults to 'sign' can be changed by
%   setting the 'SwitchingFunction' parameter. 
% 
%   See also symss/slide

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

