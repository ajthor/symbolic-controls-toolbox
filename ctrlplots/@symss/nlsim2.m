function varargout = nlsim2(sys, varargin)
%NLSIM2 Simulate a non-linear system in two variables.
%   Detailed explanation goes here

p = inputParser;
validateICs = @(IC) validateattributes(IC, {'numeric', 'cell'}, {'nonempty'});
addRequired(p, 'sys');
addOptional(p, 'tspan', [0 10]);
addOptional(p, 'x0', {[0, 0]}, validateICs);
addParameter(p, 'vars', {});
addParameter(p, 'solver', @ode45);
addParameter(p, 'trajectory', 'off');
parse(p, sys, varargin{:});

tspan = p.Results.tspan;

x0 = p.Results.x0;
if ~iscell(x0)
    x0 = {x0};
end

if nargout ~= 0 && numel(x0) > 1
    t = cell(size(x0));
    y = cell(size(x0));
end

if any(strcmp('vars', p.UsingDefaults))
    vars = sys.states(1:2);
else
    vars = cell2sym(p.Results.vars);
    if length(vars) ~= 2
        error('Incorrect number of output variables.');
    end
end

for k = 1:numel(x0)
    ic = reshape(x0{k}, [], 1);
    [ts, ys] = nlsolver(sys, tspan, ic);
    t{k} = ts;
    y{k} = ys(:, has(sys.states.', vars));
end

if nargout ~= 0
    varargout{1} = t;
    varargout{2} = y;
else
    ax = gca;
    current_state = ax.NextPlot;
    c = lines;
    
    for k = 1:numel(x0)
        ax.NextPlot = 'add';
        yp = y{k};
        h = plot(yp(:, 1), yp(:, 2));
        h.Color = c(2, :);
    end
    
    ax.NextPlot = current_state;
    ax.XLimMode = 'auto';
    ax.YLimMode = 'auto';
    ax.XLabel.String = char(vars(1));
    ax.YLabel.String = char(vars(2));
    
    if strcmp(p.Results.trajectory, 'on')
        xl = ax.XLim;
        yl = ax.YLim;
        
        X = cell(size(sys.states));
        [X{:}] = ndgrid(...
            linspace(xl(1), xl(2), 20), ...
            linspace(yl(1), yl(2), 20));
        
        nx = cell(size(sys.states));
        nx(:) = {'SUBX'};
        tx = sym(genvarname(nx, who));
        tf = subs(sys.f, sys.states, tx);
        Ffun = symfun(tf, tx);
        Y = Ffun(X{:});
        
        XVal = X(has(sys.states.', vars));
        YVal = Y(has(sys.states.', vars));
        
        ax.NextPlot = 'add';
        h = quiver(XVal{1}, XVal{2}, double(YVal{1}), double(YVal{2}));
        h.Color = c(1, :);
        
        ax.XLim = xl;
        ax.YLim = yl;
        ax.NextPlot = current_state;
    end
    
end

end

