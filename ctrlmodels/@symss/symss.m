classdef symss
    %SYMSS Construct symbolic state-space model or convert model to 
    %symbolic state-space.
    %
    %   Detailed explanation goes here
    
    properties (Access = public)
        % State matrix A
        A
        % Input matrix B
        B
        % Output matrix C
        C
        % Feed-forward matrix D
        D
    end
    
    properties (Access = public)
        %State Equations
        %   Example:
        %       syms x1 x2
        %       sys = symss;
        %       sys.states = [x1 x2];
        %       sys.f(1) = x1;
        %       sys.f(2) = x2;
        f = sym([])
        % Ouput Equations
        g = sym([])
    end
    
    properties (Access = public)
        % State Variables
        states = sym([])
        % Input Variables
        inputs = sym([])
        % Output Variables
        outputs = sym([])
    end
    
    properties (Hidden)
        f_ = sym([])
        g_ = sym([])
        A_ = sym([])
        B_ = sym([])
        C_ = sym([])
        D_ = sym([])
    end
    
    methods
        function obj = symss(varargin)
            %SYMSS Construct a symbolic state space model.
            %
            %   sys = SYMSS(A, B, C, D)
            %   Creates a state space model using the matrices A, B, C, D. 
            %       dx/dt = Ax(t) + Bx(t)
            %        y(t) = Cx(t) + Du(t)
            %   A must be an nxn matrix, B must be an nxm matrix, and C
            %   must be a pxn matrix. If D is specified, it must be a pxm
            %   matrix.
            %   
            %   sys = SYMSS(n) creates a state space model with n state
            %   variables.
            % 
            %   sys = SYMSS(____, Ts) creates a discrete state space model
            %   with sample time Ts.
            %
            %   sys = SYMSS creates an empty state space representation.
            ni = nargin;
            
            % Quick copy of class.
            if ni == 1 && isa(varargin{1}, 'symss')
                obj = varargin{1};
                return;
            end
            
            if ni ~= 0
                if ismatrix(varargin{1})
                    if ni < 3 && isscalar(varargin{1})
                        % First argument is just a number.
                        n = varargin{1};
                        obj.states = sym('x', [1 n]);
                        
                        % obj.A = sym(eye(n));
                        % obj.B = sym(zeros(n, 1));
                        % obj.B(n) = 1;
                        % obj.C = sym(zeros(1, n));
                        % obj.C(1) = 1;
                        % obj.D = sym(0);
                    else
                        % Ensure symbolic.
                        varargin = cell2sym(varargin);
                        % Define states.
                        if isValid(varargin{:}) 
                            
                        end
                    end
                else
%                         if ischar([varargin{:}])
%                         % One of the arguments is a character vector.
%                         end

                end
                    
%                     error('symss:invalidArgument', ...
%                         'Invalid argument %s of type %s', inputname(1), class(varargin{1}));
            else
                % No input arguments.
            end
            
        end
    end
    
    % Getters and setters.
    methods
        function obj = set.states(obj, varargin)
            %Set state variables for state space model.
            obj.states = reshape(cell2sym(varargin), [], 1);
        end
        
        function obj = set.inputs(obj, varargin)
            %Set input variables for the state space model.
            obj.inputs = reshape(cell2sym(varargin), [], 1);
        end
        
        function obj = set.f(obj, varargin)
            %Set state function.
            
            % If the number of functions is greater than the number of
            % states, error.
%             if numel(varargin{:}) > numel(obj.states)
%                 
%             end
            % If the functions are not the correct format, meaning they are
            % symbolic expressions, not a function of the state variables,
            % or are symbolic functions with arguments that are not
            % parameters of the state variables, error.
            args = argnames(cell2sym(varargin));
%             for k = 1:numel(args)
%                 if ~ismember(obj.states, args(k))
%                     if ~ismember(symvar(obj.states), args(k))
%                     end
%                 end
%             end
            obj.f = formula(varargin{:});
            
            [tx, tu, tf, ~] = varSub(obj);
            obj.A = jacobian(tf, tx);
            obj.A = subs(obj.A, [tx tu], [obj.states obj.inputs]);
            obj.B = jacobian(tf, tu);
            obj.B = subs(obj.B, [tx tu], [obj.states obj.inputs]);
        end
        
        function obj = set.g(obj, varargin)
            %Set output function g(x)
            obj.g = formula(varargin{:});
            [tx, tu, ~, tg] = varSub(obj);
            obj.C = jacobian(tg, tx);
            obj.C = subs(obj.C, [tx tu], [obj.states obj.inputs]);
            obj.D = jacobian(tg, tx);
            obj.D = subs(obj.D, [tx tu], [obj.states obj.inputs]);
        end
        
        function obj = set.A(obj, A)
            %Set state matrix.
            obj.A = A;
            obj.f = obj.A*obj.states + obj.B*obj.inputs;
        end
        
        function obj = set.B(obj, B)
            %Set input matrix.
            obj.B = B;
            obj.f = obj.A*obj.states + obj.B*obj.inputs;
        end
        
        function obj = set.C(obj, C)
            %Set output matrix.
            obj.C = C;
            obj.g = sys.C*sys.states + sys.D*sys.inputs;
        end
        
        function obj = set.D(obj, D)
            %Set feed-forward matrix.
            obj.D = D;
            obj.g = sys.C*sys.states + sys.D*sys.inputs;
        end
        
%         function Value = get.f(obj)
%             syms t
%             x = sym('x', [size(obj.A, 2), 1]);
%             u = sym('u', [size(obj.B, 2), 1]);
%             fun = obj.A*x + obj.B*u;
%             
%             for k = 1:numel(fun)
%                 fn = symfun(fun(k), [t, x.', u.']);
%                 Value(k) = fn;
%             end
%             Value = obj.f;
%         end
        
%         function Value = get.g(obj)
%             syms t
%             x = sym('x', [size(obj.C, 2), 1]);
%             u = sym('u', [size(obj.D, 2), 1]);
%             fun = obj.C*x + obj.D*u;
%             
%             for k = 1:numel(fun)
%                 fn = symfun(fun(k), [t, x.', u.']);
%                 Value{k} = fn;
%             end
%         end
        
%         function obj = set.f(obj, expr)
% %             disp(expr)
%             obj.f = expr;
%         end
%         
%         function obj = set.g(obj, expr)
% %             disp(expr)
%             obj.g = expr;
%         end
        
    end
    
    % Overloaded operators.
    methods (Access = public)
        function obj = mtimes(obj, P)
            %MTIMES Operator overloading to implement similarity
            %transformation syntax.
            obj = simtrans(obj, P);
        end
        
    end
    
%     methods (Access = protected)
%         function header = getHeader(obj)
%             if ~isscalar(obj)
%                 header = getHeader@matlab.mixin.CustomDisplay(obj);
%             else
%                 headerStr = matlab.mixin.CustomDisplay.getClassNameForHeader(obj);
%                 headerStr = ['Symbolic state space ', headerStr, ' with properties:'];
%                 header = sprintf('%s\n',headerStr);
%             end
%         end
%    
%         function propgrp = getPropertyGroups(obj)
%             if ~isscalar(obj)
%                 propgrp = getPropertyGroups@matlab.mixin.CustomDisplay(obj);
%             else
%                 propList1 = struct('A', obj.A, 'B', obj.B, ...
%                                    'C', obj.C, 'D', obj.D);
%                 propList2 = struct('f', obj.f, 'g', obj.g);
%                 
%                 propgrp(1) = matlab.mixin.util.PropertyGroup(propList1);
%                 propgrp(2) = matlab.mixin.util.PropertyGroup(propList2);
%             end
%         end
%     end
end
