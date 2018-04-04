function P = care(sys, varargin)
%CARE Solve the continuous algebraic Riccati equation.
%   
%   P = CARE(sys) solves the continuous algebraic Riccati equation for
%   a symbolic state-space model and returns the solution P.
% 
%   P = CARE(sys, Q, R, S) solves the continuous algebraic Riccati equation
%   using the matrices Q, R, and S. If omitted, Q defaults to I, R defaults
%   to I, and S defaults to 0.

%   References:
%   Arnold, William F., and Alan J. Laub. "Generalized eigenproblem 
%   algorithms and software for algebraic Riccati equations." Proceedings 
%   of the IEEE 72.12 (1984): 1746-1754.

p = inputParser;
[A, B, C, ~] = getabcd(sys);
% validateMatrix = @(M) isequal(M, M.') && isequal(size(A), size(M));
validateMatrix = @(M) ...
    validateattributes(M, {'sym', 'numeric'}, ...
                       {'square', 'nonnegative', 'size', size(A)});
addRequired(p, 'sys');
addOptional(p, 'Q', eye(size(A)), validateMatrix);
addOptional(p, 'R', eye(size(A)));
addOptional(p, 'S', C);
parse(p, sys, varargin{:});

Q = p.Results.Q;
if ~issymmetric(Q)
    error('Q must be symmetric.');
end

R = p.Results.R;
if ~issymmetric(R)
    error('R must be symmetric.');
end

S = p.Results.S;

H = [A, -B*inv(R)*B.'; -S.'*Q*S, -A.'];
if ~ishamiltonian(H)
    error('Could not form the Hamiltonian.');
end

% Compute the Schur decomposition.
[U, ~] = schurs(H);

% Compute the solution to the Lyapunov equation.
U = mat2cell(U, size(A), size(A));

cs = warning('off', 'all');

P = U{2, 1}/U{1, 1};

% Compute the inverse using the Moore-Penrose pseudoinverse if the
% inverse does not exist.
if any(isinf(P))
    P = U{2, 1}*pinv(U{1, 1});
end

warning(cs);


end

