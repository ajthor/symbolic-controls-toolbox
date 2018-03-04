classdef (InferiorClasses = {?sym}) symtf
    %SYMTF Construct symbolic transfer function or convert model to
    %symbolic transfer function.
    %   
    %   G = SYMTF(expr) 
    %   creates a transfer function using a symbolic expression. The
    %   symbolic expression should be a polynomial function of one of the
    %   variables {s, z, p, q}.
    %   
    %   G = SYMTF(num, den) creates a transfer function with numerator and
    %   denominator 'num' and 'den'. 'num' and 'den' can be scalar arrays
    %   or symbolic arrays representing the coefficients of a polynomial or
    %   symbolic expressions.
    %   
    %   G = SYMTF creates the transfer function G(s) = 1.
    
    properties (Access = public, Dependent)
        % Numerator
        Numerator
        % Denominator
        Denominator
        % Variable
        Variable
    end
    
    properties (SetAccess = immutable, Dependent)
        % Transfer Function
        tf
    end
    
    % Internal Properties
    properties (Access = private)
        % Numerator
        num_ = sym([])
        % Denominator
        den_ = sym([])
        % Transfer Function Variable
        tfvar_ = sym([])
    end
    
    % Constants
    properties (Access = private, Constant)
        allowed = {'s', 'z', 'p', 'q'}
    end
    
    methods
        function obj = symtf(varargin)
            %SYMTF Symbolic transfer function.
            %   Detailed explanation goes here
            ni = nargin;
            
            if ni == 1 && isa(varargin{1}, 'symtf')
                obj = varargin{1};
                return;
            end
            
            if ni ~= 0
                if ni == 1
                    if isa(varargin{1}, 'symss')
                        obj = symss2symtf(varargin{1});
                    else
                        if ischar(varargin{1})
                            if ~ismember(varargin{1}, obj.allowed)
                                error('Transfer function variable must be one of {%c %c %c %c}', obj.allowed{:});
                            end
                            obj.tfvar_ = sym(varargin{1});
                            obj.num_ = obj.tfvar_;
                            obj.den_ = 1;
                        elseif isa(varargin{1}, 'sym')
                            V = obj.getTFVar(varargin{1});
                            if ~isempty(V)
                                obj.tfvar_ = V;
                            else
                                obj.tfvar_ = sym('s');
                            end
                            
                            [N, D] = numden(varargin{1});
                            obj.num_ = coeffs(N, obj.tfvar_, 'All');
                            obj.den_ = coeffs(D, obj.tfvar_, 'All');
                        else
                            
                        end
                    end
                elseif ni == 2
                    obj.tfvar_ = sym('s');
                    obj.Numerator = varargin{1};
                    obj.Denominator = varargin{2};
                end
            else
                % No input arguments.
                obj.tfvar_ = sym('s');
                obj.num_ = 1;
                obj.den_ = 1;
            end
        end
    end
    
    methods (Hidden)
        function S = sym(obj)
            S = obj.tf;
        end
    end
    
    methods (Access = private)
        function Value = getTFVar(obj, p)
            %GETTFVAR Finds the transfer function variable in the list of
            %allowed variables.
            if isempty(obj.tfvar_)
                S = symvar(p);
                m = find(ismember(obj.allowed, S), 1);
                Value = sym(obj.allowed(m));
            else
                Value = obj.tfvar_;
            end
        end
    end
    
    % Getters and Setters
    methods  
        function Value = get.Numerator(obj)
            Value = poly2sym(obj.num_, obj.tfvar_);
        end
        function Value = get.Denominator(obj)
            Value = poly2sym(obj.den_, obj.tfvar_);
        end
        
        function obj = set.Numerator(obj, num)
            if isa(num, 'sym') && isscalar(num)
                obj.num_ = coeffs(num, obj.tfvar_, 'All');
            elseif ismatrix(num)
                obj.num_ = sym(num);
            else
                error('Invalid numerator.');
            end
        end
        function obj = set.Denominator(obj, den)
            if isa(den, 'sym') && isscalar(den)
                obj.den_ = coeffs(den, obj.tfvar_, 'All');
            elseif ismatrix(den)
                obj.den_ = sym(den);
            else
                error('Invalid numerator.');
            end
        end
        
        function Value = get.tf(obj)
            N = obj.Numerator;
            D = obj.Denominator;
            Value = N/D;
        end
        
        function Value = get.Variable(obj), Value = obj.tfvar_; end
        
        function obj = set.Variable(obj, v)
            if ~isa(v, 'sym')
                obj.tfvar_ = sym(v);
            else
                obj.tfvar_ = v;
            end
        end
    end
    
    % Overloaded operators.
    methods
        function C = plus(A, B)
            %PLUS Overloaded to allow for transfer functions to be added
            %without pole-zero cancellations.
            C = symtf;
            if ~isa(A, 'symtf')
                G = B;
                H = A;
            else
                G = A;
                H = B;
            end
            
            C.tfvar_ = G.tfvar_;
            
            if ~isa(H, 'symtf')
                if ~isa(H, 'sym')
                    H = sym(H);
                end
                
                [N, D] = numden(H);
                C.Numerator = G.Numerator*D + N*G.Denominator;
                C.Denominator = G.Denominator*D;
            else
                if G.tfvar_ ~= H.tfvar_
                    error('Transfer functions must have the same variable.');
                end
                C.Numerator = G.Numerator*H.Denominator + H.Numerator*G.Denominator;
                C.Denominator = G.Denominator*H.Denominator;
            end
        end
        
        function C = mtimes(A, B)
            %MTIMES Overloaded to allow for transfer functions to be
            %multiplied without pole-zero cancellations.
            C = symtf;
            if ~isa(A, 'symtf')
                G = B;
                H = A;
            else
                G = A;
                H = B;
            end
            
            C.tfvar_ = G.tfvar_;
            
            if ~isa(H, 'symtf')
                if ~isa(H, 'sym')
                    H = sym(H);
                end
                
                [N, D] = numden(H);
                C.Numerator = G.Numerator*N;
                C.Denominator = G.Denominator*D;
            else
                if G.tfvar_ ~= H.tfvar_
                    error('Transfer functions must have the same variable.');
                end
                C.Numerator = G.Numerator*H.Numerator;
                C.Denominator = G.Denominator*H.Denominator;
            end
        end
        
        function C = mrdivide(A, B)
            %MRDIVIDE Overloaded to allow for transfer functions to be
            %divided without pole-zero cancellations.
            C = symtf;
            if ~isa(A, 'symtf')
                G = B;
                G.Numerator = B.Denominator;
                G.Denominator = B.Numerator;
                H = A;
            else
                G = A;
                H = B;
            end
            
            C.tfvar_ = G.tfvar_;
            
            if ~isa(H, 'symtf')
                C.Numerator = G.Numerator;
                C.Denominator = G.Denominator*H;
            else
                if G.tfvar_ ~= H.tfvar_
                    error('Transfer functions must have the same variable.');
                end
                C.Numerator = G.Numerator*H.Denominator;
                C.Denominator = G.Denominator*H.Numerator;
            end
        end
        
        function C = mpower(A, B)
            %MPOWER Overloaded to allow for transfer functions to use the
            %matrix power operator without pole-zero cancellations.
            C = symtf;
            if ~isa(A, 'symtf')
                G = B;
                H = A;
            else
                G = A;
                H = B;
            end
            
            C.tfvar_ = G.tfvar_;
            
            if ~isa(H, 'symtf')
                C.Numerator = G.Numerator^H;
                C.Denominator = G.Denominator^H;
            else
                if G.tfvar_ ~= H.tfvar_
                    error('Transfer functions must have the same variable.');
                end
                
                C.Numerator = G.Numerator^H;
                C.Denominator = G.Denominator^H;
            end
        end
    end
    
end

