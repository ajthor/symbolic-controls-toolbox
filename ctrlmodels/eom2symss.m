function sys = eom2symss(eqns, states)
%EQN2SYMSS Creates a state space model from symbolic equations of motion.
%   
%   sys = EOM2SYMSS(eqns, states)
%   
%   Creates a state space model according to the following rules:
%       1. Differentiate the states to opbtain the state equations.
%           .
%           x = d/dt(x)
%       2. For any derivatives of the states that are not also states,
%       solve the equations for the derivatives and replace them in the
%       state equations.

p = inputParser;
validateSym = @(S) isa(S, 'sym');
addRequired(p, 'eqns', validateSym);
addRequired(p, 'states', validateSym);

parse(p, eqns, states);

sys = symss;
sys.states = states;

funs = diff(sys.states);
if has(funs, 'diff')
    % Get all unique higher derivatives.
    D = unique(getSymbolicDerivatives(eqns));
    D = setdiff(D, sys.states);
    
    % Create temporary variable names so that we can solve.
    nd = cell(size(D));
    nd(:) = {'DX'};
    td = sym(genvarname(nd, who));
    
    funs = subs(funs, D, td);
    teqns = subs(eqns, D, td);
    
    % Solve the equations for the temporary variables.
    S = solve(teqns, td);
    
    % Replace the temporary variables with solutions.
    funs = subs(funs, S);
end

sys.f = funs;

% nx = cell(size(sys.states));
% nx(:) = {'SUBX'};
% 
% nu = cell(size(sys.inputs));
% nu(:) = {'SUBU'};
% 
% tx = sym(genvarname(nx, who));
% tu = sym(genvarname(nu, who));

% if ~isLowIndexDAE(eqns, [sys.states; sys.inputs])
%     [newEqs,newVars,R,oldIndex] = reduceDAEIndex(eqns, [sys.states; sys.inputs]);
% end

% if has(eqns, 'diff')
%     D = unique(getSymbolicDerivatives(eqns));
%     DX = setdiff(D, sys.states);
%     
%     nd = cell(size(DX));
%     nd(:) = {'DX'};
%     td = sym(genvarname(nd, who));
%     
% %     eqns = subs(formula(eqns), DX, td);
% end

% eqns = subs(formula(eqns), [sys.states; sys.inputs], [tx; tu]);

% for k = 1:numel(sys.states)
%     der = diff(sys.states(k));
%     mems = ismember(der, sys.states);
%     memd = ismember(der, DX);
%     if any(mems)
%         sys.f(k) = der;
%     elseif any(memd)
%         dder = td(memd);
%         S = solve(eqns, dder);
%     end
% end

% x = sym('x', [numel(states), 1]);
% u = sym('u', [numel(inputs), 1]);
% y = sym('y', [numel(outputs), 1]);
% 
% Dx = sym('Dx', [numel(states), 1]);
% Y = sym('y', [numel(outputs), 1]);
% 
% % Needed for differentiation w/rt 't'.
% syms t
% 
% for k = 1:numel(states)
%     % Start off with a differentiated state.
%     Dx(k) = diff(states(k), t);
%     
%     % If the differentiated state is a member of the states variable, we
%     % assign it to the element in the states variable. If it isn't, we need
%     % to solve for it in the system of equations given as a parameter.
%     if ismember(Dx(k), states)
%         index = ismember(states, Dx(k));
%         Dx(k) = Dx(k) == states(index);
%     else
%         % Cycle through the equations given and solve for the variable of
%         % interest. We use the function 'isolate' here to reorder the
%         % equation and save it.
%         for n = 1:numel(f)
%             try
%                 Dx(k) = isolate(f(n), diff(states(k), t));
%                 % If the equation is solvable for the variable, we end the
%                 % for loop, using the first equation that is solvable for
%                 % the variable of interest.
%                 break
%             catch ME
%                 % If the equation is not solvable for the variable, catch
%                 % the error and continue on to the next equation.
%                 switch ME.identifier
%                     case 'symbolic:solve:EquationUnsolvableFor'
%                         % Potentially display a warning.
%                         % warning('Equation not solvable for variable.')
%                     otherwise
%                         rethrow(ME)
%                 end
%                 % If the variable of interest is not solvable in the
%                 % current set of equations, we throw an error.
%                 if n == numel(f)
%                     warning(['The variable ', Dx(k), ' is not solvable in the current set of equations.'])
%                 end
%             end
%         end
%     end
% end
% 
% for k = 1:numel(outputs)
%     % Cycle through the output equations and solve for the given output
%     % variable. In a simple case, the output equations could be formatted:
%     % y == x1
%     % This means the output variable is y. 
%     for n = 1:numel(g)
%         try
%             Y(k) = isolate(g(n), outputs{k});
%             break
%         catch ME
%             switch ME.identifier
%                 case 'symbolic:solve:EquationUnsolvableFor'
%                     % Potentially display a warning.
%                     % warning('Equation not solvable for variable.')
%                 otherwise
%                     rethrow(ME)
%             end
%         end
%     end
% end
% 
% % Once we have the Dx vector containing the differentiated state variables,
% % we can substitute the x vector into the right-hand side of Dx, which are 
% % the functions f_i(x).
% f_eqns = subs(rhs(Dx), states, x.');
% f_eqns = subs(f_eqns, inputs, u.');
% 
% g_eqns = subs(rhs(Y), states, x.');
% g_eqns = subs(g_eqns, inputs, u.');
% 
% % Then we can compute the jacobians and get A, B, C, and D.
% A = jacobian(f_eqns, x);
% B = jacobian(f_eqns, u);
% C = jacobian(g_eqns, x);
% D = jacobian(g_eqns, u);
% 
% % Assign the state variables passed as parameters to the x vector.
% for k = 1:numel(states)
%     x(k) = states{k};
% end
% 
% % Assign the input variables passed as parameters to the u vector.
% for k = 1:numel(inputs)
%     u(k) = inputs{k};
% end
% 
% for k = 1:numel(outputs)
% %     y(k) = isolate(g(k), outputs{k})
%     y(k) = outputs{k};
% end

end

