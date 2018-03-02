function y = initial(sys, varargin)
%INITIAL Compute the zero state response of a system.
%   y = INITIAL(sys)
%   y = INITIAL(sys, x0)

u = 0;

if nargout == 0
    lsim(sys, u, varargin{:});
else
    y = lsim(sys, u, varargin{:});
end

% ni = nargin;
% if ~isa(sys, 'symss')
%     error('sys must be a symbolic state space model.');
% end
% 
% A = sys.A;
% C = sys.C;
% if isempty(C)
%     error('Invalid output matrix.');
% end
% 
% if ni == 2
%     if numel(varargin{1}) ~= size(A, 1)
%         error('Dimensions do not match.');
%     end
%     x0 = reshape(varargin{1}, [], 1);
% else
%     x0 = zeros(size(A, 1), 1);
% end
% 
% syms s t
% phi = ilaplace(stm(sys), s, t);
% y = C*phi*x0;
% 
% if nargout == 0
%     h = fplot(y);
%     h.XRange = [0 10];
% %     xlabel('t');
% %     ylabel('y');
% end

end

