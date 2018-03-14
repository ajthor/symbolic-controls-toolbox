function varargout = nlsim(sys, varargin)
%NLSIM Simulate a non-linear system in one variable.
%   Detailed explanation goes here

p = inputParser;
validateX0 = @(x0) ...
    validateattributes(x0, {'numeric'}, {'nonempty'});
addRequired(p, 'sys');
addOptional(p, 'tspan', [0 10]);
addOptional(p, 'x0', [0, 0], validateX0);
addParameter(p, 'vars', {});
addParameter(p, 'solver', @ode45);
parse(p, sys, varargin{:});

tspan = p.Results.tspan;

x0 = p.Results.x0;

vars = cell2sym(p.Results.vars);
if length(vars) > 1
    error('Too many output variables.');
end

[t, ys] = nlsolver(sys, tspan, x0);
y = ys(:, has(sys.states.', vars));

if nargout ~= 0
    varargout{1} = t;
    varargout{2} = y;
else
    plot(t, y)
    ax = gca;
    ax.XLim = tspan;
    ax.XLimMode = 'auto';
    ax.XLabel.String = 'Time (seconds)';
    ax.YLabel.String = 'Amplitude';
end

% % syms t
% % A = sys.A;
% % [M, ~] = eig(A);
% % Jr = jordan(A);
% % M = sym('M', size(A));
% % Jr = jordan(A);
% % S = solve(M\A*M == Jr, M);
% % SC = struct2cell(S);
% % M = subs(M, S);
% 
% % xt = M*exp(Jr*t)/M;
% 
% tx = sym(genvarname({'SUBX', 'SUBX'})).';
% xt = subs(xt, sys.states, tx);
% 
% [x1_0, x2_0] = meshgrid(-3:3);
% [X1, X2] = meshgrid(linspace(-3, 3, 20));
% 
% hold on
% for k = 1:numel(x1_0)
%     y = xt*[x1_0(k); x2_0(k)];
%     y = subs(y, tx, {X1; X2});
%     fplot(y(1), y(2), [0 5]);
% end
% hold off
% 
% Phi = stm(sys);
% y = eye(2)*ilaplace(Phi, s, t);
% 
% ty = subs(y, sys.states, tx);
% 
% % Ffun = symfun(subs(sys.f, sys.states, tx), [t; tx]);
% % F = matlabFunction(Ffun, 'vars', {t; tx});
% % F = @(t, tx.') = 
% [X1, X2] = meshgrid(-3:3);
% % [X, Y] = meshgrid([-1 1]);
% for k = 1:numel(X1)
%     x1_0 = [X1(k); X2(k)];
%     tyi = ty*x1_0;
% %     y = initial(sys, [x10 x20]);
% %     y = subs(y, sys.states, tx);
%     [ts, ys] = ode45(F, [0 5], [x10 x20]);
%     plot(ys(:, 1), ys(:, 2));
% end
% hold off
% 
% % p = inputParser;
% % validateSys = @(sys) isa(sys, 'symss');
% % validateArg = @(arg) isa(arg, 'sym');
% % addRequired(p, 'sys', validateSys);
% % addRequired(p, 'X', validateArg);
% % addRequired(p, 'Y', validateArg);
% % addOptional(p, 'xlim', [-2 2]);
% % addOptional(p, 'ylim', [-2 2]);
% % parse(p, sys, varargin{:});
% % 
% % X = p.Results.X;
% % Y = p.Results.Y;
% % xlim = p.Results.xlim;
% % if numel(xlim) == 2
% %     xlim = linspace(xlim(1), xlim(2), 10);
% % end
% % ylim = p.Results.ylim;
% % if numel(ylim) == 2
% %     ylim = linspace(ylim(1), ylim(2), 10);
% % end
% % 
% % [Xlim, Ylim] = meshgrid(xlim, ylim);
% % g = {Xlim, Ylim};
% % 
% % nx = cell(size(sys.states));
% % nx(:) = {'SUBX'};
% % x = sym(genvarname(nx));
% % tf = subs(sys.f, sys.states, x);
% % 
% % gr = gradient(sys.A*sys.states, [X, Y]);
% % F1 = subs(tf(1), x.', g);
% % F2 = subs(tf(2), x.', g);
% % quiver(Xlim, Ylim, F1, F2)

end

