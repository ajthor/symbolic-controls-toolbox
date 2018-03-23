function P = care(sys, Q, R)
%CARE Solve the continuous algebraic Riccati equation.
%   Detailed explanation goes here

p = inputParser;
[A, B, C, ~] = getmatrices(sys);

% validateattributes(Q, {'sym', 'numeric'}, {'square', 'size', size(A)});
% validateattributes(R, {'sym', 'numeric'}, {'square', 'ncols', size(B, 2)});

validateSymmetric = @(A) isequal(A, A.');
addRequired(p, 'sys');
addRequired(p, 'Q', validateSymmetric);
addRequired(p, 'R', validateSymmetric);

parse(p, sys, Q, R);

Q = sym(Q);
R = sym(R);
M = C;

P = sym('P', size(A));

H = [A, -B*inv(R)*B.'; -M.'*Q*M, -A.'];
% H = [A, -B*inv(R)*B.'; -Q, -A.'];

[V, D] = eig(H);
rV = V(:, ~all(isAlways(real(D) < 0) == 0, 1));
XY = mat2cell(rV, [length(A), length(A)]);

P = real(XY{2}/XY{1});

end

