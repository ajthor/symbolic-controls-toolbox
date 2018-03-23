function y = lsim(sys, u, varargin)
%LSIM Compute the linear response of a system to arbitrary inputs.
% 
%   y = LSIM(sys, u) computes the linear response of a system to an
%   arbitrary input where 'u' is a symbolic s-domain input signal.
% 
%   y = LSIM(sys, u, x0) computes the linear response of a system with
%   initial conditions.
% 
%   y = LSIM(sys, u, t) computes the linear response of a system to an
%   arbitrary input where 'u' is time-series data and 't' is a time vector.
%   
%   y = LSIM(sys, u, t, x0) computes the linear response of a system to an
%   arbitrary input where 'u' is time-series data, 't' is a time vector,
%   and 'x0' are the initial conditions.
% 
%   NOTE: Non-linear systems are linearized about the initial conditions
%   passed to the function. 

% p = inputParser;
% addRequired(p, 'sys');
% addRequired(p, 'u');
% addOptional(p, 't');
% addOptional(p, 'x0');
% parse(p, sys, u, varargin{:});

ni = nargin;

[A, B, C, ~] = sys.getmatrices();

if (isempty(u) || u ~= 0) && isempty(B)
    error('Invalid input matrix.');
elseif isempty(C)
    error('Invalid output matrix.');
end

if ni == 3
    if numel(varargin{1}) ~= size(A, 1)
        error('Dimensions do not match.');
    end
    x0 = reshape(varargin{1}, [], 1);
else
    x0 = zeros(size(A, 1), 1);
end

% Get the zero input response and the zero state response.
if isa(u, 'sym')
    Yi = zir(sys, x0);
    Ys = zsr(sys, u);
    
    if ~isempty(Ys)
        Y = Yi + Ys;
    else
        Y = Yi;
    end

    syms s t
    y = ilaplace(Y, s, t);
else
    yi = tzir(sys, x0);
    ys = tzsr(sys, u);
    y = yi + ys;
end

y = subs(y, sys.states, x0);

if nargout == 0
    if length(y) == 1
        fplot(y);
        ax = gca;
        ax.XLim = [0 10];
        ax.XLimMode = 'auto';
        xlabel('Time (seconds)');
        ylabel('Amplitude');
    else
        [m, n] = size(y);
        for k = 1:numel(y)
            subplot(n, m, k)
            fplot(y(k));
            ax = gca;
            ax.XLim = [0 10];
            ax.XLimMode = 'auto';
            xlabel('Time (seconds)');
            ylabel('Amplitude');
            title(['Output ', num2str(m), ' for input ', num2str(n)]);
        end
    end
end

end

