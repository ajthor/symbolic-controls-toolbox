function S = slide(sys, varargin)
%SLIDE Computes a sliding surface for a system.
%   Detailed explanation goes here

% References:
% Shtessel, Yuri, et al. Sliding mode control and observation. Vol. 10. New
% York: Birkhäuser, 2014.
% 
% Edwards, Christopher. Sliding mode schemes using output information with
% application to heating plant problems. Diss. Engineering, 1995.
% 
% Ghaffari, Azad, and Mohammad Javad Yazdanpanah. "Computing optimized
% nonlinear sliding surfaces." Control and Decision Conference, 2008. CCDC
% 2008. Chinese. IEEE, 2008.

p = inputParser;
[A, B, ~, ~] = getabcd(sys);
addRequired(p, 'sys', @(S) validatesystem(S, {'hasinputs'}));
addOptional(p, 'Q', eye(size(A)));
addOptional(p, 'Lambda', sym.empty);
parse(p, sys, varargin{:});

Q = p.Results.Q;

n = size(A, 1);
m = size(B, 2);

% Compute regular form coordinate transformation matrix Tr.
[T, ~] = qr(B);
ex = fliplr(eye(n));
Tr = ex*T.';

ns = [n - m, m];

Abar = mat2cell(Tr*A*Tr.', ns, ns);
Qbar = mat2cell(Tr*Q*Tr.', ns, ns);

Ahat = Abar{1, 1} - Abar{1, 2}/Qbar{2, 2}*(Qbar{1, 2}.');
Qhat = Qbar{1, 1} - Qbar{1, 2}/Qbar{2, 2}*(Qbar{1, 2}.');

% Form the Hamiltonian for solving the ARE.
H = [Ahat, -Abar{1, 2}/Qbar{2, 2}*(Abar{1, 2}.'); -Qhat, -Ahat.'];

% Solve the Hamiltonian.
[U, ~] = schurs(H);
U = mat2cell(U, size(H)/2, size(H)/2);
Phat = U{2, 1}/U{1, 1};

% Calculate M.
M = Qbar{2, 2}\(Qbar{1, 2}.') + Qbar{2, 2}\(Abar{1, 2}.')*Phat;

% Calculate S.
if ~any(strcmp('Lambda', p.UsingDefaults))
    Lambda = p.Results.Lambda;
    Bbar = Tr*B;
    B2 = Bbar(end - m + 1:end, end - m + 1:end);
    S2 = Lambda/B2;
else
    S2 = eye(m);
end

S = S2*[M, eye(m)]*Tr;

end

