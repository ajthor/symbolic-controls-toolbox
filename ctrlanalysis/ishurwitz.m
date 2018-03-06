function tf = ishurwitz(varargin)
%ISHURWITZ Returns logical 1 (true) if the matrix or transfer function is
%Hurwitz, or logical 0 (false) if it is not.
%   
%   tf = ISHURWITZ(sys) tests for Hurwitz conditions in a symbolic
%   state-space model.
%   
%   tf = ISHURWITZ(A) tests for Hurwitz conditions on a state matrix.
%   
%   tf = ISHURWITZ(G) tests for Hurwitz conditions on a symbolic transfer
%   function.

if isa(varargin{1}, 'symss')
    sys = symss(varargin{1});
    [A, ~, ~, ~] = getMatrices(sys);
    tf = ~any(real(eig(A)) >= 0);
elseif isa(varargin{1}, 'symtf')
    p = pole(varargin{1});
    tf = ~any(real(p) >= 0);
else
    if isa(varargin{1}, 'sym')
        % Symbolic expression. Treat it like a transfer function.
        p = poles(varargin{:});
        tf = ~any(real(p) >= 0);
    elseif ismatrix(varargin{1}) && issquare(varargin{1})
        % Square matrix. 
        tf = ~any(real(eig(varargin{1})) >= 0);
    else
        error('Invalid argument.');
    end
end
    
end

