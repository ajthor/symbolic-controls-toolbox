function [V, P, dV] = lyap(sys, varargin)
%LYAP Solves the lyapunov equation for a system.
%   
%   V = LYAP(sys) 
%   solves the Lyapunov matrix equation A.'*P + P*A + Q == 0 for the
%   symbolic state space model and returns the equation V = x.'*P*x. The
%   function solves the Lyapunov matrix equation using the Hamiltonian
%   matrix H = [A, 0; -Q, -A.'].
%   
%   V = LYAP(sys, Q) solves the Lyapunov matrix equation for the symbolic
%   state space model using the matrix Q. If Q is unspecified, the function
%   uses the identity matrix I.
% 
%   [V, P, dV] = LYAP(sys, Q) solves the Lyapunov matrix equation and
%   returns the Lyapunov function, the solution P, and the Lyapunov
%   function derivative.
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
%   - In almost all cases, use a linearized system for nonlinear state
%   space models to compute the Lyapunov equation.
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

% if any(isinf(P))
%     warning('Could not solve the Hamiltonian.');
%     warning('Attempting to solve symbolically.');
% 
%     P = sym('P', size(A));
%     S = solve(A.'*P + P*A == -Q, P);
%     P = subs(P, S);
% 
%     if isempty(P)
%         error('Could not find a solution to the Lyapunov equation.');
%     end
% end


V = sys.states.'*P*sys.states;
dV = -sys.states.'*Q*sys.states;

warning(cs);

% [V, D] = eig(H);
% 
% if isequal(size(V), size(H)) % && ~any(imag(diag(D)))
%     [~, idx] = sort(diag(real(D)));
%     V = V(:, idx);
%     U = mat2cell(V, size(A), size(A));
%     P = U{2, 1}/U{1, 1};
% else
%     warning('Could not solve the Hamiltonian.');
%     warning('Attempting to solve symbolically.');
%     
%     P = sym('P', size(A));
%     S = solve(A.'*P + P*A == -Q, P);
%     P = subs(P, S);
% end


% METHOD 1
% % % Construct Hamiltonian
% H = [A, zeros(size(A)); -Q, -A.'];
% % [U, ~] = schurs(H);
% [V, D] = eig(H);
% V = orth(V, 'skipnormalization');
% % [~, idx] = sort(diag(D));
% % V = V(:, idx);
% % U = V;
% [U, ~] = qr(V, 'real');
% U = mat2cell(U, size(A), size(A));
% P = U{2, 1}/U{1, 1};

% METHOD 2
% H = [A, eye(size(A)); -Q, -A.'];
% [V, D] = eig(H);
% D = reshape(diag(D), 1, []);
% 
% % rL = D(~all(isAlways(real(D) < 0) == 0, 1));
% % rV = cellfun(@(L) {null(H - L*eye(size(H)))}, sym2cell(rL));
% 
% rV = V(:, ~all(isAlways(real(D) < 0) == 0, 1));
% XY = mat2cell(rV, [length(A), length(A)]);
% 
% P = XY{2}/XY{1};

% METHOD 3
% P = sym('P', size(A));
% S = solve(A.'*P + P*A == -Q, P);
% P = subs(P, S);

% METHOD 4
% H = [A, eye(size(A)); -Q, -A.'];
% [V, D, p] = eig(H);
% VV = zeros(size(H));
% for k = 1:size(V, 2)
%     idx = p(k);
%     L = any(D == D(idx, idx), 1);
%     VV(:, L) = repmat(V(:, k), 1, nnz(L));
% end
% 
% XY = VV(:, ~any(isAlways(real(diag(D)) < 0) == 0, 2));
% XY = mat2cell(XY, [length(A), length(A)]);
% 
% P = XY{2}/XY{1};

% METHOD 6
% [U, ~] = eig(A);
% [V, ~] = eig(Q);
% S = U.'*A*U;
% T = V.'*A*V;

% AH = feval(symengine, 'linalg::hessenberg', A);
% [S, ~] = qr(AH);

end

