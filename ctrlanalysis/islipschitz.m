function tf = islipschitz(f, varargin)
%ISLIPSCHITZ Returns logical 1 (true) if a function is Lipschitz at a point
%or logical 0 (false) if it is not.
% 
%   ISLIPSCHITZ tests for continuous differentiability first, and then
%   checks for lipschitz conditions by 
%   
%   tf = ISLIPSCHITZ(f) tests for Lipschitz continuity on the interval
%   (-Inf Inf). The function uses symvar to determine the variable.
%   
%   tf = ISLIPSCHITZ(f, var) tests for Lipschitz continuity on the interval
%   (-Inf Inf) with respect to the variable 'var'.
% 
%   tf = ISLIPSCHITZ(f, var, pt) tests for Lipschitz continuity at a point
%   'pt' respect to the variable 'var'.
%   
%   tf = ISLIPSCHITZ(f, var, x1, x2) tests for Lipschitz continuity on an
%   interval [x1, x2].

p = inputParser;
verifyNum = @(N) isnumeric(N);
verifySym = @(S) validateattributes(S, {'sym'}, {'nonempty'});
addRequired(p, 'f', verifySym);
addOptional(p, 'var', [], verifySym);
addOptional(p, 'x1', -Inf, verifyNum);
addOptional(p, 'x2', Inf, verifyNum);

parse(p, f, varargin{:});

if any(strcmp('var', p.UsingDefaults))
    S = symvar(f);
    idx = find(ismember(S, {'t', 's', 'p', 'z', 'q', 'x', 'y', 'z'}), 1);
    if isempty(idx)
        V = S(1);
    else
        V = S(idx);
    end
else
    V = p.Results.var;
end

x1 = p.Results.x1;
x2 = p.Results.x2;
if ~any(strcmp('x1', p.UsingDefaults))
    
    if ~any(strcmp('x2', p.UsingDefaults))
        
    elseif x2 < x1
        error('Invalid bounds x2 < x1.');
    end
end
% if nargin == 3
%     pt = x1;
% else
%     pt = [];
% end

% if ~isa(f, 'sym')
%     error('Argument must be a symbolic function.');
% end
% 
% switch nargin
%     case 1
%         S = symvar(f);
%         idx = find(ismember(S, {'t', 's', 'p', 'z', 'q', 'x', 'y', 'z'}), 1);
%         V = S(idx);
%         x1 = -Inf;
%         x2 = Inf;
%     case 2
%         V = varargin{1};
%         x1 = -Inf;
%         x2 = Inf;
%     case 3
%         V = varargin{1};
%         x1 = varargin{2};
%         x2 = NaN;
%     case 4
%         V = varargin{1};
%         x1 = varargin{2};
%         x2 = varargin{3};
%         
% end
% 
% if ~isa(V, 'sym')
%     if ischar(V)
%         V = sym(V);
%     else
%         error('Second argument must be a symbolic variable.');
%     end
% end

% if nargin > 1
%     V = varargin{1};
%     if ~isa(V, 'sym')
%         if ischar(V)
%             V = sym(V);
%         else
%             error('Second argument must be a symbolic variable.');
%         end
%     end
%     
%     if nargin >= 3
%         if numel(varargin{2}) > 2
%             error('Interval has too many elements.');
%         end
%         
%         x1 = varargin{2};
%         if x2 > x1(1)
%             error('Lower bound is greater than upper bound.')
%         end
%     else
%         x1 = [-Inf Inf];
%     end
% else
%     S = symvar(f);
%     idx = find(ismember(S, {'t', 's', 'p', 'z', 'q', 'x', 'y', 'z'}), 1);
%     V = S(idx);
%     x1 = 0;
% end

% Test for continuous differentiability.
if numel(x1) == 1
    try
        df = diff(f, V);
        flim = limit(df, V, x1);
        tf = isnan(flim);
        if tf
            dffun = symfun(df, V);
            tf = isequal(flim, dffun(x1));
        end
    catch ME
        if strcmp(ME.identifier, 'symbolic:kernel:DivisionByZero')
            tf = false;
            return;
        else
            rethrow(ME);
        end
    end
else
    df = diff(f, V);
    dcont = feval(symengine, 'discont', df, V);
    tf = ~any(isAlways(x1 <= dcont && dcont <= x2));
end
    
% Test for Lipschitz conditions.
if ~tf
    minfun = symfun(-abs(diff(f, V)), V);
    try
%         options = optimset('PlotFcns',@optimplotfval);
%         options = optimset('FunValCheck', 'on');
        [x, fval, exitflag] = fminbnd(minfun, x1, x2);
    catch ME
        if strcmp(ME.identifier, 'MATLAB:fminbnd:checkfun:NaNFval')
            warning('Could not determine supremum of function.');
            tf = false;
        else
            rethrow(ME)
        end
    end
    tf = ~isnan(fval);
    
    if ~tf
        
    end
%     [~, D] = numden(f);
%     dg = length(coeffs(D, V, 'All'));
%     sols = solve(D, V, 'MaxDegree', dg, 'Real', true);

%     tf = ~any(sols == rg);
end

end

