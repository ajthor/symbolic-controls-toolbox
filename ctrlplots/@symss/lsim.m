function y = lsim(sys, u, varargin)
%LSIM Compute the linear response of a system to arbitrary inputs.
% 
%   y = LSIM(sys, u) computes the linear response of a system to an
%   arbitrary input where 'u' is an s-domain input signal.
% 
%   y = LSIM(sys, u, x0) computes the linear response of a system with
%   initial conditions.
% 
%   y = LSIM(sys, u, t) computes the linear response of a system to an
%   arbitrary input where 'u' is time-series data and 't' is a time vector.
%   
%   y = LSIM(sys, u, t, x0) computes the linear response of a system to an
%   arbitrary input where 'u' is time-series data, 't' is a time vector,
%   and 'x0' are the initial conditions.
ni = nargin;
if ~isa(sys, 'symss')
    error('sys must be a symbolic state space model.');
end

[A, B, C, D] = sys.getMatrices();

if (isempty(u) || u ~= 0) && isempty(B)
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
%     y = conv(double(v), reshape(u, 1, []), 'same');
% else
    Y = G*u;
    y = ilaplace(Y, s, t);
    yi = C*ilaplace(Phi, s, t)*x0;
% end

if isempty(y)
    y = yi;
else
    y = y + yi;
end

if nargout == 0
    h = fplot(y);
%     h.XRange = [0 10];
%     xlabel('t');
%     ylabel('y');
end

end

