function G = symss2symtf(sys)
%SYMSS2SYMTF Convert a symbolic state space model to a symbolic transfer
%function.
%   
%   G = SYMSS2SYMTF(sys)
%   converts a symbolic state space model to a symbolic transfer function
%   using the formula:
%       G = C*((s*I - A)^-1)*B + D

validabcd(sys);
[A, B, C, D] = sys.getabcd();

syms s
G = C/(s*eye(size(A)) - A)*B + D;
G = symtf(G);

end

