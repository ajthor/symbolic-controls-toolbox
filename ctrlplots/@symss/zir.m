function Yi = zir(sys, x0)
%ZIR Get the zero input response of a system.
%   The zero input response is defined as:
% 
%                    -1
%   Yi(s) = C(sI - A)  x(0)
% 
%   And equivalently in the time domain:
%   
%             At
%   yi(t) = Ce  x(0)
% 

p = inputParser;
validateSys = @(S) islinear(S.f, S.states);
validateICs = @(IC) validateattributes(IC, {'sym', 'numeric'}, {'nonempty'});
addRequired(p, 'sys', validateSys);
addRequired(p, 'x0', validateICs);
parse(p, sys, x0);

[~, ~, C, ~] = getabcd(sys);
Phi = stm(sys);

Yi = C*Phi*x0;

end

