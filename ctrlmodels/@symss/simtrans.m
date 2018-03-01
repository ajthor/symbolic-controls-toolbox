function [A, B, C, D] = simtrans(sys, P)
%SIMTRANS State space similarity transformation.
% 
%   [A, B, C, D] = SIMTRANS(sys, P) uses a similarity transform matrix, P,
%   to perform a similarity transform on system and returns the state space
%   matrices.
%
%   [A, B, C, D] = sys*P similarity transform shorthand.

p = inputParser;
validateSys = @(sys) isa(sys, 'symss');
validateP = @(P) validateattributes(P, ...
    {'numeric', 'sym'}, {'square', 'nonempty'});
addRequired(p, 'sys', validateSys);
addRequired(p, 'P', validateP);
parse(p, sys, P);

if ~isa(P, 'sym')
    P = sym(P);
end

% Substitute the values into the state matrices.
A = P*sys.A/P;
B = P*sys.B;
C = sys.C/P;
D = sys.D;

end

