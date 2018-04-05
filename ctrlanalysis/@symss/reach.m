function varargout = reach(sys, x, varargin)
%REACH Computes a backward-reachable region for a given state.
%   
%   

p = inputParser;
addRequired(p, 'sys', @(S) validatesystem(S, {'full'}));
addRequired(p, 'x');
addParameter(p, 'Points', 20);
addParameter(p, 'Ts', 1E-3);
addParameter(p, 'Tf', 10);
addParameter(p, 'ZeroSpacing', 1E-3);
addParameter(p, 'ComputationTime', 30);
addParameter(p, 'Trajectory', false);
parse(p, sys, x, varargin{:});

np = p.Results.Points;
zs = p.Results.ZeroSpacing;
t = p.Results.ComputationTime;

Ts = p.Results.Ts;
Tf = p.Results.Tf/Ts;

[tx, ~, tf, ~] = varsub(sys);
PFfun = symfun(tf, tx);

% Compute the negative gradient at the point.
% Move backward and 

% Create polar circle and convert to cartesian.
R = [zs*ones([np + 1, 1]), linspace(0, 2*pi, np + 1).'];
R = R(1:end - 1, :);
R = [R(:, 1).*cos(R(:, 2)), R(:, 1).*sin(R(:, 2))];

% Move to current point.
R = R + x{:};
PF = R;

k = 0;

orig = warning('off');

tic
while true
    k = k + Ts;
    
    % Compute the trajectories.
    nPF = PFfun(PF(:, 1), PF(:, 2));
    nPF = reshape(nPF, 1, []);
    nPF = double(cell2sym(nPF))*Ts;
    
%     nPF = nPF./vecnorm(nPF, 2, 2);
    
    % Take the negative gradient.
    nPF = PF - nPF;
    
%     plot(R(:, 1), R(:, 2), 'o')
%     hold on
%     plot(nPF(:, 1), nPF(:, 2), 'o')
%     quiver(PF(:, 1), PF(:, 2), nPF(:, 1), nPF(:, 2));
%     hold off
%     
    
    % Remove points within the shape.
    b = boundary(R);
    inR = inpolygon(nPF(:, 1), nPF(:, 2),...
        R(b, 1), R(b, 2));
    
    b = boundary(nPF);
    inPF = inpolygon(R(:, 1), R(:, 2),...
        nPF(b, 1), nPF(b, 2));
    
    % Add new points. 
    R = [R(~inPF, :); [nPF(~inR, 1), nPF(~inR, 2)]];
    
%     % Remove points within the boundary.
%     b = boundary(R, 0.75);
%     inR = inpolygon(R(:, 1), R(:, 2),...
%         R(b, 1), R(b, 2));
%     
%     R = R(~inR, :);
    
    % Set new starting points.
    PF = nPF;

    if k >= Tf
        break;
    elseif toc > t
        warning(orig);
        warning('Computation time exceeded.');
        break;
    end
end

warning(orig);

if nargout ~= 0
    varargout{1} = R;
    varargout{2} = PF;
else
    b = boundary(R);
    plot(R(b, 1), R(b, 2));
    
%     rgx = xlim;
%     rgy = ylim;
% 
%     ax = gca;
%     axcs = ax.NextPlot;
%     
%     % Plot function trajectories.
%     if p.Results.Trajectory
%         ax.NextPlot = 'add';
%         
%         [X, Y] = meshgrid(linspace(rgx(1), rgx(2), 20), ...
%                           linspace(rgy(1), rgy(2), 20));
%                   
%         F1 = subs(sys.f(1), sys.states, {X; Y});
%         F2 = subs(sys.f(2), sys.states, {X; Y});
%         
%         q = quiver(ax, X, Y, F1, F2);
%         q.AutoScale = 'on';
%         q.AlignVertexCenters = 'on';
%     end
%     
%     ax.NextPlot = axcs;
end

end

