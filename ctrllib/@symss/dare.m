function [P, K] = dare(sys, varargin)
%DAR Summary of this function goes here
%   Detailed explanation goes here

% References:
% Ku?era, Vladimír. "The discrete Riccati equation of optimal control."
% Kybernetika 8.5 (1972): 430-447.

p = inputParser;
[A, B, ~, ~] = getabcd(sys);
% validateMatrix = @(M) isequal(M, M.') && isequal(size(A), size(M));
validateMatrix = @(M) ...
    validateattributes(M, {'sym', 'numeric'}, ...
                       {'square', 'nonnegative', 'size', size(A)});
addRequired(p, 'sys');
addOptional(p, 'Q', eye(size(A)));
addOptional(p, 'R', eye(size(A)));
addParameter(p, 'exact', false);
parse(p, sys, varargin{:});

Q = p.Results.Q;
if ~issymmetric(Q)
    error('Q must be symmetric.');
end

R = p.Results.R;
if ~issymmetric(R)
    error('R must be symmetric.');
end

Ai = inv(A).';
Ri = inv(R);

BB = B*Ri*B.';
% CC = C.'*Q*C;
CC = Q;

% Form the symplectic matrix.
H = [A + BB*Ai*CC, -BB*Ai; -Ai*CC, Ai]

% Solve the continuous algebraic Riccati equation using the Hamiltonian.
P = slvdham(H, 'exact', p.Results.exact);

% Compute the gain matrix, K.
K = (R + B.'*P*B)\B.'*P*A;

end

