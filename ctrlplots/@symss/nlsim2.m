function varargout = nlsim2(sys, varargin)
%NLSIM2 Simulate a non-linear system in two variables.
%   Detailed explanation goes here

p = inputParser;
validateX0 = @(x0) ...
    validateattributes(x0, {'numeric', 'cell'}, {'nonempty'});
addRequired(p, 'sys');
addOptional(p, 'tspan', [0 10]);
addOptional(p, 'x0', {[0, 0]}, validateX0);
addParameter(p, 'vars', {});
addParameter(p, 'solver', @ode45);
addParameter(p, 'trajectory', 'off');
parse(p, sys, varargin{:});

tspan = p.Results.tspan;

x0 = p.Results.x0;
if nargout ~= 0 && numel(x0) > 1
    t = cell(size(x0));
    y = cell(size(x0));
end

vars = cell2sym(p.Results.vars);

solver = p.Results.solver;
if ~any(strcmp(func2str(solver), {'ode45', 'ode23', 'ode113', ...
        'ode15s', 'ode23s', 'ode23t', 'ode23tb'}))
    error('Invalid ODE solver.');
end

for k = 1:numel(x0)
    [ts, ys] = nlsolver(sys, tspan, x0{k});
    
    if nargout == 0
        yp = ys(:, has(sys.states.', vars));
        plot(yp(:, 1), yp(:, 2));
    end
    
    t{k} = ts;
    y{k} = ys;
end

if nargout ~= 0
    varargout{1} = t;
    varargout{2} = y;
else
    ax = gca;
    ax.XLimMode = 'auto';
    xl = ax.XLim;
    yl = ax.YLim;
    ax.XLabel.String = char(vars(1));
    ax.YLabel.String = char(vars(2));
end

% if strcmp(p.Results.trajectory, 'on')
%     [X1, X2] = meshgrid(...
%         linspace(xl(1), xl(2), 20), ...
%         linspace(yl(1), yl(2), 20));
% %         F1 = subs(sys.f, 
% end

end

