function y = lsim(sys, u, varargin)
%LSIM Compute the linear response of a system to arbitrary inputs.
%   y = LSIM(sys, u)
%   y = LSIM(sys, u, x0)
ni = nargin;
if ~isa(sys, 'symss')
    error('sys must be a symbolic state space model.');
end

A = sys.A;
B = sys.B;
C = sys.C;
D = sys.D;
if isempty(B)
    error('Invalid input matrix.');
elseif isempty(C)
    error('Invalid output matrix.');
end

if ni == 3
    if numel(varargin{1}) ~= size(A, 1)
        error('Dimensions do not match.');
    end
    x0 = reshape(varargin{1}, [], 1);
else
    x0 = zeros(size(A, 1), 1);
end

syms s t
Phi = stm(sys);
G = C*Phi*B + D;
% if ~isa(u, 'sym')
%     rg = 1:numel(u);
%     g = ilaplace(G, s, t);
%     v = subs(g, t, rg);
%     y = conv(reshape(u, 1, []), double(v), 'same');
% else
    Y = G*u;
    y = ilaplace(Y, s, t);
    yi = C*ilaplace(Phi, s, t)*x0;
% end

if nargout == 0
    h = fplot(y + yi);
    h.XRange = [0 5];
%     xlabel('t');
%     ylabel('y');
end

end

