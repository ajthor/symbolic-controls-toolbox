classdef symss
    %SYMSS Construct symbolic state-space model or convert model to 
    %symbolic state-space.
    %
    %   Detailed explanation goes here
    
    properties (SetAccess = private, Dependent)
        % State matrix A
        A
        % Input matrix B
        B
        % Output matrix C
        C
        % Feed-forward matrix D
        D
    end
    
    properties (Dependent, AbortSet = true)
        %State Equations
        f
        % Ouput Equations
        g
    end
    
    properties (Dependent)
        % State Variables
        states
        % Input Variables
        inputs
    end
    
    properties (Access = private)
        % Internal Variables
        f_ = sym([])
        g_ = sym([])
        
        states_ = sym([])
        inputs_ = sym([])
        params_ = sym([])
        
        A_ = sym([])
        B_ = sym([])
        C_ = sym([])
        D_ = sym([])
    end
    
    % Constructor.
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
            %   sys = SYMSS(states, inputs) creates a state space model
            %   using the state variables and input variables provided.
            %   
            %   sys = SYMSS(n) creates a state space model with n state
            %   variables. Get the state variables from the 'states'
            %   property in order to use them in a state equation.
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
                    if ni == 1 && isscalar(varargin{1})
                        % First argument is just a number.
                        n = varargin{1};
                        obj.states_ = sym('x', [1, n]);
                    elseif ni == 2 && ...
                            isa(varargin{1}, 'sym') && ...
                            isa(varargin{2}, 'sym')
                        obj.states_ = cell2sym(varargin(1));
                        obj.inputs_ = cell2sym(varargin(2));
                    elseif ni == 4
                        % Ensure symbolic.
                        for k = 1:ni
                            varargin{k} = sym(varargin{k});
                        end
                        
                        if isValid(varargin{:}) 
                            n = size(varargin{1}, 1);
                            m = size(varargin{2}, 2);
                            obj.states_ = sym('x', [1, n]);
                            
                            obj.f = varargin{1}*obj.states_.';
                            obj.g = varargin{3}*obj.states_.';
                            
%                             if (all(varargin{2} == 0) - m) ~= 0
                            if all(varargin{2} == 0)
                                obj.inputs_ = sym('u', [1, m]);
                                obj.f = obj.f_ + varargin{2}*obj.inputs_.';
                                obj.g = obj.g_ + varargin{4}*obj.inputs_.';
                            end
                        end
                    else
                        error('symss:invalidArgument', ...
                            'Invalid argument of type %s', class(varargin{1}));
                    end
                else
                    error('symss:invalidArgument', ...
                        'Invalid argument of type %s', class(varargin{1}));
                end
            else
                % No input arguments.
            end
        end
    end
    
    % Getters and setters.
    methods
        function obj = set.states(obj, varargin)
            %Set state variables for state space model.
            obj.states_ = reshape(cell2sym(varargin), [], 1);
            obj.params_ = setdiff(symvar(cell2sym(varargin)), obj.states_);
        end
        function obj = set.inputs(obj, varargin)
            %Set input variables for the state space model.
            obj.inputs_ = reshape(cell2sym(varargin), [], 1);
            obj.params_ = setdiff(symvar(cell2sym(varargin)), obj.inputs_);
        end
        
        function states = get.states(obj), states = obj.states_; end
        function inputs = get.inputs(obj), inputs = obj.inputs_; end
        
        function obj = set.f(obj, varargin)
            %Set state function f(x)
            obj.f_ = formula(varargin{:});
            [tx, tu, tf, ~] = varSub(obj);
            obj.A_ = jacobian(tf, tx);
            obj.B_ = jacobian(tf, tu);
            obj.A_ = subs(obj.A_, [tx tu], [obj.states_ obj.inputs_]);
            obj.B_ = subs(obj.B_, [tx tu], [obj.states_ obj.inputs_]);
        end
        function obj = set.g(obj, varargin)
            %Set output function g(x)
            obj.g_ = formula(varargin{:});
            [tx, tu, ~, tg] = varSub(obj);
            obj.C_ = jacobian(tg, tx);
            obj.D_ = jacobian(tg, tu);
            obj.C_ = subs(obj.C_, [tx tu], [obj.states_ obj.inputs_]);
            obj.D_ = subs(obj.D_, [tx tu], [obj.states_ obj.inputs_]);
        end
        
        function f = get.f(obj)
            f = obj.f_.';
%             [tx, tu, tf, ~] = varSub(obj);
%             f = cell(size(tf)).';
%             for k = 1:numel(tf)
%                 f{k} = symfun(tf(k), [obj.params_; obj.states_ obj.inputs_]); 
%                 f{k} = subs(f{k}, [tx, tu], [obj.states_ obj.inputs_]);
%             end            
        end
        function g = get.g(obj), g = obj.g_.'; end
        
        function A = get.A(obj), A = simplify(obj.A_); end
        function B = get.B(obj), B = simplify(obj.B_); end
        function C = get.C(obj), C = simplify(obj.C_); end
        function D = get.D(obj), D = simplify(obj.D_); end
    end
    
    % Overloaded operators.
    methods (Access = public)
        function obj = mtimes(obj, P)
            %MTIMES Operator overloading to implement similarity
            %transformation syntax.
            obj = simtrans(obj, P);
        end
    end
end
