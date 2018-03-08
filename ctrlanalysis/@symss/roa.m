function R = roa(sys, V, varargin)
%ROA Calculate region of attraction for a nonlinear system.
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
%   The result R is the greatest solution to the equation.
% 
%   ROA(sys, V) plots the region of attraction for a state space model
%   using a given Lyapunov equation.

DV = diff(V);
Dx = diff(sys.states);

if isequal(DV, 0)
    error('Unable to calculate derivative of V. Try using symbolic functions such as x1(t).');
end

[tx, ~, ~, ~] = varsub(sys);

DV = subs(DV, Dx, sys.f);

V = formula(subs(V, sys.states, tx));
DV = formula(subs(DV, sys.states, tx));

try
    sols = solve(DV, tx);
    sols = struct2cell(sols);
    if ~isempty(sols)
        Vfun = symfun(V, tx);
        R = double(max(Vfun(sols{:})));
    end
    
    if nargout == 0 && numel(sys.states) <= 2
    
        % Plot ROA curve.
        fi = fimplicit(V == R);
        
        hold on
        rgx = fi.XRange*1.5;
        rgy = fi.YRange*1.5;
        fi.XRange = rgx;
        fi.YRange = rgy;
        fi.XRangeMode = 'auto';
        fi.YRangeMode = 'auto';
        
        [X, Y] = meshgrid(linspace(rgx(1), rgx(2), 20), ...
                          linspace(rgy(1), rgy(2), 20));
        
        % Plot VDot contours.
%         fimplicit(DV)
%         Ffun = matlabFunction(symfun(tf, tx));
%         [XX, YY] = meshgrid(linspace(rgx(1), rgx(2), 3), linspace(rgy(1), rgy(2), 3));
%         [ts,ys] = ode45(Ffun,[0,50],[XX; YY]);
        Z = subs(DV, tx, {X; Y});
        contour(X, Y, Z, 0:5);
        
        % Plot function trajectories.
        F1 = subs(sys.f(1), sys.states, {X; Y});
        F2 = subs(sys.f(2), sys.states, {X; Y});
        q = quiver(X, Y, F1, F2);
        q.AutoScale = 'on';
        q.AlignVertexCenters = 'on';
        
        title('Region of Attraction');
        xlabel(char(sys.states(1)));
        ylabel(char(sys.states(2)));
        legend({'Region of Attraction', '$\dot{V}$', 'Trajectories'}, 'Interpreter', 'latex');
        hold off
    end
    
catch ME
    if strcmp(ME.identifier, 'something')
        % do something
    else
        rethrow(ME)
    end
end

end

