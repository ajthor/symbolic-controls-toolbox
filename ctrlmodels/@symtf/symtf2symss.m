function sys = symtf2symss(varargin)
%SYMTF2SYMSS Convert a symbolic transfer function to a symbolic state space
%model.
% 
%   sys = SYMTF2SYMSS(sys)
%   converts a symbolic transfer function to a symbolic state space model.

if ~isa(varargin{1}, 'symtf')
    if isa(varargin{1}, 'sym') || ismatrix(varargin{1})
        G = symtf(varargin{:});
    else
        error('Argument is not a symbolic transfer function.');
    end
else
    G = varargin{1};
end

n = max([numel(G.num_) numel(G.den_)]) - 1;

b = G.num_/G.den_(1);
a = G.den_/G.den_(1);
a = [zeros(1, length(b) - length(a)), a];
b = [zeros(1, length(a) - length(b)), b];

A = sym(zeros(n));
A(1:end - 1, 2:end) = eye(n - 1);
A(end, :) = fliplr(-a(2:end));

B = sym([zeros(n - 1, 1); 1]);

C = fliplr(b(2:end)) - fliplr(a(2:end))*b(1);

D = sym(b(1));

sys = symss(A, B, C, D);
    
end

