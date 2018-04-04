function [P, V, dV] = lyap(sys, varargin)
%LYAP Solves the lyapunov equation for a system.
%   
%   P = LYAP(sys) solves the Lyapunov matrix equation for a symbolic
%   state-space model and returns the solution P.
%   
%   P = LYAP(sys, Q) solves the Lyapunov matrix equation for a symbolic
%   state space model using the matrix Q. If omitted, Q defaults to I.
% 
%   [P, V, dV] = LYAP(sys, Q) solves the Lyapunov matrix equation and
%   returns the solution P, the Lyapunov function V = x.'*P*x, and the
%   Lyapunov function derivative dV = -x.'*Q*x.
% 
%   Methodology:
%   The Hamiltonian of (A, Q) is formed in order to solve the Lyapunov
%   equation A.'P + PA = -Q. If the Hamiltonian has linearly independent
%   eigenvectors, no zero eigenvalues, and no repeated eigenvalues, we can
%   use the Schur decomposition to compute the matrix P.
% 
%   We sort the eigenvalues so that the eigenvectors corresponding to
%   stable eigenvectors appear in U_11 and U_21 and compute U_21*U_11^-1.
%   
%   In the case of a defective matrix, the inverse may not produce the
%   actual inverse of the matrix. In these cases, the Moore-Penrose
%   pseudoinverse is used. See PINV for more information.
% 
%   Tips:
%   - In almost all cases, it is necessary to use a linearized system for
%   nonlinear state space models to compute the Lyapunov equation.
% 
%   - Rank-deficient state matrices will not produce a unique result, and
%   the P matrix may not be symmetric. Check the rank of A before running
%   the function.
% 
%   See also symss/care, lyap, dlyap, pinv

%   References:
%   Arnold, William F., and Alan J. Laub. "Generalized eigenproblem 
%   algorithms and software for algebraic Riccati equations." Proceedings 
%   of the IEEE 72.12 (1984): 1746-1754.
% 
%   Laub, Alan. "A Schur method for solving algebraic Riccati equations." 
%   IEEE Transactions on automatic control 24.6 (1979): 913-921.
% 
%   https://stanford.edu/class/ee363/lectures/clqr.pdf
%   http://www2.mpi-magdeburg.mpg.de/mpcsc/mitarbeiter/saak/lehre/Matrixgleichungen/pyuantong_09WS.pdf
%   https://www.cs.cornell.edu/~bindel/class/cs6210-f16/lec/2016-11-02.pdf

p = inputParser;
[A, ~, ~, ~] = getabcd(sys);
validateMatrix = @(M) isequal(M, M.') && isequal(size(M), size(A));
addRequired(p, 'sys')
addOptional(p, 'Q', eye(size(A)), validateMatrix);
parse(p, sys, varargin{:});

Q = p.Results.Q;

% Form the Hamiltonian.
H = [A, zeros(size(A)); -Q, -A.'];
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

V = sys.states.'*P*sys.states;
dV = -sys.states.'*Q*sys.states;

warning(cs);

end

