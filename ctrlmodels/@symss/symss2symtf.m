function G = symss2symtf(varargin)
%SYMSS2SYMTF Convert a symbolic state space model to a symbolic transfer
%function.
%   
%   G = SYMSS2SYMTF(sys)
%   converts a symbolic state space model to a symbolic transfer function
%   using the formula:
%       G = C*((s*I - A)^-1)*B + D

ni = nargin;

if ni == 1 && isa(varargin{1}, 'symss')
    sys = varargin{1};
    [A, B, C, D] = sys.getMatrices();
elseif ni == 4
    A = varargin{1};
    B = varargin{2};
    C = varargin{3};
    D = varargin{4};
end

if isempty(A) || isempty(B) || isempty(C)
    error('System is not fully defined.');
end

syms s
G = C/(s*eye(size(A)) - A)*B + D;
G = symtf(G);

end

