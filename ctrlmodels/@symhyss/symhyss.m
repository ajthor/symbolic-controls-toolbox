classdef (SupportExtensionMethods = true) symhyss < symss
    %SYMHYSS Construct symbolic hybrid state-space model.
    %   
    %   hsys = SYMHYSS creates an empty hybrid state-space representation.
    %
    %   A hybrid state-space model is defined by both continuous and
    %   discrete dynamics along with switching conditions.
    %
    %   Define system dynamics by specifying the state equations and the
    %   condition for the dynamics of each state. The first index
    %   corresponds to the set of dynamics for a state. The second index
    %   defines the equation in the dynamics. For example,
    %                              .
    %       f(1, 3) corresponds to x3 = f3(t, x, u) in the first state.
    %
    %   Example (Thermostat):
    %       syms x a
    %       sys = symhyss
    %       sys.states = x
    %       
    %       sys.f(1, 1) = -a*x
    %       sys.cond(1) = x >= 20
    %       
    %       sys.f(2, 1) = -a*(x - 30)
    %       sys.cond(2) = x <= 22
    %
    %   Accessing specific dynamics and conditions can be done using
    %   indexing. Otherwise, the dynamics and conditions are returned as
    %   elements of an array. For example,
    %
    %       [f1, f2, ...] = sys.f
    %       [c1, c2, ...] = sys.cond
    
    % Dependent properties.
    properties (Dependent, AbortSet = true)
        % Switching Conditions
        cond
    end
    
    % Internal properties.
    properties (Access = private)
        % 1xn cell array. Each column represents distinct dynamics. Each
        % element in the cell array is a 1xm symbolic array.
        f_ = cell.empty(1, 0)
        
        cond_ = cell.empty(1, 0)
    end
    
    % Constructor
    methods
        function obj = symhyss(varargin)
            %SYMHYSS Construct an instance of this class
            %   Detailed explanation goes here
            ni = nargin;
            
            if ni == 1 && isa(varargin{1}, 'symhyss')
                obj = varargin{1};
                return;
            end
            
            if ni ~= 0
                % Handle states.
                if isscalar(varargin{1})
                    % First argument is numeric.
                    n = varargin{1};
                    obj.states_ = sym('x', [n, 1]);
                elseif isa(varargin{1}, 'sym')
                    obj.states = varargin(1);
                else
                    error('symhyss:invalidArgument', ...
                          'Invalid argument to symhyss constructor.');
                end

                % Handle inputs.
                if isscalar(varargin{2})
                    % Second argument is numeric.
                    m = varargin{2};
                    obj.inputs_ = sym('u', [m, 1]);
                elseif isa(varargin{2}, 'sym')
                    obj.inputs = varargin(2);
                else
                    error('symhyss:invalidArgument', ...
                          'Invalid argument to symhyss constructor.');
                end
            else
                % No output arguments.
            end
        end
    end
    
    % Getters and setters.
    methods
        function obj = set.cond(obj, varargin)
            % Set switching conditions for hybrid state-space model.
            obj.cond_ = privSetCond(obj, varargin{:});
        end
        
        function cond = get.cond(obj)
            cond = privGetCond(obj);
        end
    end
    
    % Overloaded protected methods.
    methods (Access = protected)
        function obj = privSetF(obj, varargin)
            if nargin == 2
                obj.f_ = varargin{:};
            else
                idx = varargin{1};
                if numel(obj.f_) < idx(1)
                    d = sym.empty(0, 1);
                    d(idx(2)) = cell2sym(varargin(2:end));
                else
                    d = obj.f_{idx(1)};
                    d(idx(2:end)) = cell2sym(varargin(2:end));
                end
                
                obj.f_(idx(1)) = {reshape(d, [], 1)};
            end
        end
        function f = privGetF(obj, varargin)
            if nargin == 1
                f = obj.f_;
            else
                idx = varargin(1);
                if numel(idx{:}) == 1
                    f = obj.f_{idx{:}};
                else
                    d = obj.f_{idx{1}};
                    f = d{idx{2}};
                end
            end
        end
        
        function A = privGetA(obj, varargin)
            [tx, tu, tf, ~] = varsub(obj);
            
            if nargin == 1
                for k = 1:numel(tf)
                    A{k} = jacobian(tf(k), tx);
                    A{k} = subs(A{k}, [tx; tu], [obj.states; obj.inputs]);
                end
            else
                idx = varargin(1);
                if numel(idx{:}) == 1
                    f = tf(idx{:});
                else
                    error('Index is out of range.');
                end

                A = jacobian(f, tx);
                A = subs(A, [tx; tu], [obj.states; obj.inputs]);
            end
        end
        function B = privGetB(obj, varargin)
            [tx, tu, tf, ~] = varsub(obj);
            
            if nargin == 1
                for k = 1:numel(tf)
                    B{k} = jacobian(tf(k), tu);
                    B{k} = subs(B{k}, [tx; tu], [obj.states; obj.inputs]);
                end
            else
                idx = varargin(1);
                if numel(idx{:}) == 1
                    f = tf(idx{:});
                else
                    error('Index is out of range.');
                end

                B = jacobian(f, tu);
                B = subs(B, [tx; tu], [obj.states; obj.inputs]);
            end
        end
    end
    
    % Overloadable protected methods.
    methods (Access = protected)
        function obj = privSetCond(obj, varargin)
            if nargin == 2
                obj.cond_ = varargin{:};
            else
                idx = varargin{1};
                obj.cond_(idx) = varargin(2);
            end
        end
        function cond = privGetCond(obj, varargin)
            if nargin == 1
                cond = obj.cond_;
            else
                idx = varargin(1);
                cond = obj.cond_{idx{:}};
            end
        end
    end
    
    % Overloaded subsref & subsasgn.
    methods
        function varargout = subsref(obj, S)
            switch S(1).type
                case '.'
                    if numel(S) > 1
                        idx = cell2mat(S(2).subs);
                        
                        switch S(1).subs
                            case 'f'
                                varargout = {privGetF(obj, idx)};
                            case 'cond'
                                varargout = {privGetCond(obj, idx)};
                            case 'A'
                                varargout = {privGetA(obj, idx)};
                            case 'B'
                                varargout = {privGetB(obj, idx)};
                            otherwise
                                varargout = builtin('subsref', obj, S);
                        end
                    else
                        varargout = builtin('subsref', obj, S);
                    end
                otherwise
                    varargout = builtin('subsref', obj, S);
            end
        end
        
        function obj = subsasgn(obj, S, varargin)
            switch S(1).type
                case '.'
                    if numel(S) > 1
                        idx = cell2mat(S(2).subs);
                        
                        switch S(1).subs
                            case 'f'
                                obj = privSetF(obj, idx, varargin{:});
                            case 'cond'
                                obj = privSetCond(obj, idx, varargin{:});
                            otherwise
                                obj = builtin('subsasgn', obj, S, varargin{:});
                        end
                    else
                        obj = builtin('subsasgn', obj, S, varargin{:});
                    end
                otherwise
                    obj = builtin('subsasgn', obj, S, varargin{:});
            end
        end
    end
end

