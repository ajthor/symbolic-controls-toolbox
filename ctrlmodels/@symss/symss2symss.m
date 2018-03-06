function T = symss2symss(sys, P)
%SYMSS2SYMSS State space similarity transformation.
% 
%   sys = SYMSS2SYMSS(sys, P) uses a similarity transform matrix, P, to
%   perform a similarity transform on system.
%   
%   The new state space model has the following form:
%       Dx = (P*A/P)x + (P*B)u
%        y = (C/P) + D

validateattributes(P, {'numeric', 'sym'}, {'square', 'nonempty'});
if ~isa(P, 'sym')
    P = sym(P);
end

[A, B, C, D] = sys.getmatrices();

A = P*A/P;
B = P*B;
C = C/P;
D = D;

T = sys;
T.f = A*T.states + B*T.inputs;
T.g = C*T.states + D*T.inputs;

end

