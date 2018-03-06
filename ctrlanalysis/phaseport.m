function phaseport(sys, varargin)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here
% 
%   TODO:
%   - Add checking to ensure no symbolic variables are unset.
%   - Add capability to select which variables to analyze.
p = inputParser;
validateSys = @(sys) isa(sys, 'symss');
validateArg = @(arg) isa(arg, 'sym');
addRequired(p, 'sys', validateSys);
addRequired(p, 'X', validateArg);
addRequired(p, 'Y', validateArg);
addOptional(p, 'xlim', [-2 2]);
addOptional(p, 'ylim', [-2 2]);
parse(p, sys, varargin{:});

X = p.Results.X;
Y = p.Results.Y;
xlim = p.Results.xlim;
if numel(xlim) == 2
    xlim = linspace(xlim(1), xlim(2), 10);
end
ylim = p.Results.ylim;
if numel(ylim) == 2
    ylim = linspace(ylim(1), ylim(2), 10);
end

[Xlim, Ylim] = meshgrid(xlim, ylim);
g = {Xlim, Ylim};

nx = cell(size(sys.states));
nx(:) = {'SUBX'};
x = sym(genvarname(nx));
tf = subs(sys.f, sys.states, x);

gr = gradient(sys.A*sys.states, [X, Y]);
F1 = subs(tf(1), x.', g);
F2 = subs(tf(2), x.', g);
quiver(Xlim, Ylim, F1, F2)

end

