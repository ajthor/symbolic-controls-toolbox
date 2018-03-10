function tf = islinear(f, V)
%ISLINEAR Checks for linearity of a function f(x).
%   
%   tf = ISLINEAR(f, V)
%   checks for linearity of a function using additivity and homogeneity.

syms a b
tx = sym(genvarname({'SUBX'}));
tf = subs(formula(f), V, tx);
Ffun = symfun(tf, tx);

% Disable warnings.
orig_state = warning('off','all');

try
    % Additivity
    tf = isAlways(Ffun(a) + Ffun(b) == Ffun(a + b));
    % Homogeneity
    if tf
        tf = isAlways(Ffun(a*b) == a*Ffun(b));
    end
catch ME
    warning(orig_state);
    if strcmp(ME.identifier, 'something')
        % do something
    else
        rethrow(ME);
    end
end

% Restore warnings.
warning(orig_state);

end

