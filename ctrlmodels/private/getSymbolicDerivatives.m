function D = getSymbolicDerivatives(expr)
%GETSYMBOLICDERIVATIVES Finds all symbolic derivatives in expression.
%   Detailed explanation goes here

% syms t
% vars = symvar(expr);
% vars = vars(vars ~= t);

ch = expr;

% Isolate derivatives by removing all terms that do not contain
% derivatives.
while true
    nch = children(ch);
    if iscell(nch)
        nch = cell2sym(nch);
    end
    
    if ~any(has(nch, {'diff', 'int'}))
        break;
    end
    
    ch = nch(has(nch, {'diff', 'int'}));
end

D = ch;

end

