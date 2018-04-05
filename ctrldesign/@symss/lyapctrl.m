function u = lyapctrl(sys, V)
%LYAPCTRL Computes a control input using a control Lyapunov function.
%   
%   u = LYAPCTRL(sys, V) computes a control input using Sontag's formula
%   using the control Lyapunov function V.

%   References:
%   Khalil, Hassan K. "Noninear systems." 
%   Prentice-Hall, New Jersey 2.5 (1996): 5-1.

p = inputParser;
[A, ~, ~, ~] = getabcd(sys);
addRequired(p, 'sys', @(S) validatesystem(S, {'full'}));
addRequired(p, 'V');
parse(p, sys, V);

% Find f(x) and g(x).
f = cell([size(A, 1), 1]);
g = cell([size(A, 1), 1]);

for k = 1:numel(sys.f)
    C = coeffs(sys.f(k), sys.inputs, 'All');
    if numel(C) == 2
        f{k} = C(2);
        g{k} = C(1);
    else
        f{k} = C;
        g{k} = 0;
    end
end

f = cell2sym(f).';
g = cell2sym(g).';

% Find dV.
dV = gradient(V, sys.states);

dVf = dV*f;
dVg = dV*g;

% Sontag's formula.
u = -(dVf + sqrt((dVf)^2 + (dVg)^4))/(dVg);

end

