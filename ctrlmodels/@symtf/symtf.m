classdef symtf
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
    end
    
    properties (SetAccess = immutable, Dependent)
        % Transfer Function
        tf
    end
    
    % Internal Properties
    properties (Access = private)
        % Numerator
        num_ = []
        % Denominator
        den_ = []
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
                obj.tfvar_ = sym('s');
                obj.num_ = 1;
                obj.den_ = 1;
            end
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
                obj.num_ = num;
            else
                error('Invalid numerator.');
            end
        end
        function obj = set.Denominator(obj, den)
            if isa(den, 'sym') && isscalar(den)
                obj.den_ = coeffs(den, obj.tfvar_, 'All');
            elseif ismatrix(den)
                obj.den_ = den;
            else
                error('Invalid numerator.');
            end
        end
        
        function Value = get.tf(obj)
            N = obj.Numerator;
            D = obj.Denominator;
            Value = N/D;
        end
    end
    
    % Overloaded operators.
    methods
        function C = plus(A, B)
            if A.tfvar_ ~= B.tfvar_
                error('Transfer functions must have the same variable.');
            end
            N = A.Numerator*B.Denominator + B.Numerator*A.Denominator;
            D = A.Denominator*B.Denominator;
            C = symtf(N, D);
            C.tfvar_ = A.tfvar_;
        end
        
        function C = mtimes(A, B)
            if A.tfvar_ ~= B.tfvar_
                error('Transfer functions must have the same variable.');
            end
            N = A.Numerator*B.Numerator;
            D = A.Denominator*B.Denominator;
            C = symtf(N, D);
            C.tfvar_ = A.tfvar_;
        end
    end
    
end

