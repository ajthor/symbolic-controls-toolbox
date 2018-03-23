function R = roa(sys, varargin)
%ROA Calculate region of attraction for a nonlinear system.
%   
%   R = ROA(sys) calculates the region of attraction for a state space
%   system using the Lyapunov function derived from the Lyapunov equation.
% 
%   R = ROA(sys, V) calculates the region of attraction for a state space
%   model using a given Lyapunov equation.
%   
%   To calculate the region of attraction, the system performs the
%   following steps:
%   1. Calculate the derivative of the Lyapunov function.
%   2. Obtain solutions for:
%       .
%       V = 0
%   3. Solve for the equation:
%       V(z), where 'z' are the solutions to the previous equation.
% 
%   The result R is the greatest solution to the equation V(z) = R.
% 
%   ROA(____) plots the region of attraction for a state space model
%   using a given Lyapunov equation.

p = inputParser;
addRequired(p, 'sys');
addOptional(p, 'V', sym([]));
parse(p, sys, varargin{:});
        
if any(strcmp('V', p.UsingDefaults))
    V = lyap(sys);
else
    V = p.Results.V;
end

[tx, tu, tf, ~] = varsub(sys);
tv = subs(V, [sys.states; sys.inputs], [tx; tu]);

dV = gradient(tv, tx).'*reshape(tf, [], 1);
dV = subs(dV, [sys.states; sys.inputs], [tx; tu]);

% tv = subs(V, [sys.states; sys.inputs], [tx; tu]);

% if isequal(dV, 0)
%     error('Unable to calculate derivative of V.');
% end

% DV = subs(DV, Dx, sys.f);

% V = formula(subs(V, sys.states, tx));
% DV = formula(subs(DV, sys.states, tx));

try
    sols = solve(dV, tx);
    sols = struct2cell(sols);
    if ~isempty(sols)
        Vfun = symfun(tv, tx);
        R = double(max(Vfun(sols{:})));
    end
    
catch ME
    if strcmp(ME.identifier, 'something')
        % do something
    else
        rethrow(ME)
    end
end

if nargout == 0 && numel(sys.states) <= 2
    % Plot ROA curve.
    fi = fimplicit(Vfun == R);

    rgx = fi.XRange*1.5;
    rgy = fi.YRange*1.5;
    fi.XRange = rgx;
    fi.YRange = rgy;
    fi.XRangeMode = 'auto';
    fi.YRangeMode = 'auto';

    [X, Y] = meshgrid(linspace(rgx(1), rgx(2), 20), ...
                      linspace(rgy(1), rgy(2), 20));

    ax = gca;
    current_state = ax.NextPlot;
    ax.NextPlot = 'add';

    % Plot VDot.
%         fimplicit(ax, DV)
%         Z = subs(DV, tx, {X; Y});
%         contour(X, Y, Z, 0:5);

    % Plot function trajectories.
    F1 = subs(sys.f(1), sys.states, {X; Y});
    F2 = subs(sys.f(2), sys.states, {X; Y});
    q = quiver(ax, X, Y, F1, F2);
    q.AutoScale = 'on';
    q.AlignVertexCenters = 'on';

%         ax.Title.String = 'Region of Attraction';
%         ax.XLabel.String = char(sys.states(1));
%         ax.XLabel.Interpreter = 'latex';
%         
%         ax.YLabel.String = char(sys.states(2));
%         ax.YLabel.Interpreter = 'latex';
%         
%         ax.Legend.String(1) = 'Region of Attraction';
%         ax.Legend.String(2) = '$\dot{V}$';
%         ax.Legend.String(3) = 'Trajectories';
%         ax.Legend.Interpreter = 'latex';

    title('Region of Attraction');
    xlabel(char(sys.states(1)), 'Interpreter', 'latex');
    ylabel(char(sys.states(2)), 'Interpreter', 'latex');
%         legend({'Region of Attraction', '$\dot{V}$', 'Trajectories'}, 'Interpreter', 'latex');
    legend({'Region of Attraction', 'Trajectories'}, 'Interpreter', 'latex');

    ax.NextPlot = current_state;
end

end

