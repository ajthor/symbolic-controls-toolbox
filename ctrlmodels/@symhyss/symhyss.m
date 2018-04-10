classdef symhyss < symss
    %SYMHYSS Construct symbolic hybrid state-space model.
    %   
    %   hsys = SYMHYSS creates an empty hybrid state-space representation.
    %
    %   A hybrid state-space model is defined by both continuous and
    %   discrete dynamics along with switching conditions.
    %
    %   Define system dynamics by specifying the state equations and the
    %   condition for the dynamics in the 
    
    % State Equations
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
                if ismatrix(varargin{1})
                    if ni == 1 && isscalar(varargin{1})
                        % First argument is just a number.
                        n = varargin{1};
                        obj.states_ = sym('x', [n, 1]);
                    elseif ni == 2 && ...
                           isa(varargin{1}, 'sym') && ...
                           isa(varargin{2}, 'sym')
                        obj.states = varargin(1);
                        obj.inputs = varargin(2);
                    else
                        error('symhyss:invalidArgument', ...
                              'Invalid arguments to symhyss constructor.');
                    end
                else
                    error('symhyss:invalidArgument', ...
                          'Invalid argument of type %s', ...
                          class(varargin{1}));
                end
            else
                % No output arguments.
            end
        end
    end
    
    % Getters and Setters
    methods
        function obj = set.cond(obj, varargin)
            % Set switching conditions for hybrid state-space model.
            obj.cond_ = privSetCond(obj, varargin{:});
        end
        
        function cond = get.cond(obj)
            cond = privGetCond(obj);
        end
    end
    
    % Overloaded Protected Methods
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
    end
    
    % Overloadable Protected Methods
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
    
    % Custom subsref & subsasgn
    methods
        function varargout = subsref(obj, S)
            switch S(1).type
                case '.'
                    if strcmp(S(1).subs, 'f') && numel(S) > 1
                        idx = cell2mat(S(2).subs);
                        varargout = {privGetF(obj, idx)};
                    elseif strcmp(S(1).subs, 'cond') && numel(S) > 1
                        idx = cell2mat(S(2).subs);
                        varargout = {privGetCond(obj, idx)};
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
                    if strcmp(S(1).subs, 'f') && numel(S) > 1
                        idx = cell2mat(S(2).subs);
                        obj = privSetF(obj, idx, varargin{:});
                    elseif strcmp(S(1).subs, 'cond') && numel(S) > 1
                        idx = cell2mat(S(2).subs);
                        obj = privSetCond(obj, idx, varargin{:});
                    else
                        obj = builtin('subsasgn', obj, S, varargin{:});
                    end
                otherwise
                    obj = builtin('subsasgn', obj, S, varargin{:});
            end
        end
    end
end

