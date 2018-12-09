classdef (SupportExtensionMethods = true, InferiorClasses = {?sym}) randomvar < handle
    %RANDOMVAR Symbolic random variable.

    properties (Access = {?statespace}, Hidden)
        % C Pointer Handle
        cobj_;

        % C Pointer Handle for Distribution
        dobj_;
    end

    properties
        distribution_name
    end

    methods
        function obj = randomvar(name, d, varargin)
            validateattributes(name, {'char'}, {'nonempty'});
            validateattributes(d, {'randomdistribution'}, {'nonempty'});
            validateattributes(varargin, {'cell'}, {'nonempty'});

            if ~isvarname(name)
                error('SYMCTRL::InvalidVariable', 'Invalid variable name.');
            end

            c = symctrl.mat2se(name);
            cptr = libpointer('stringPtrPtr', c);

            obj.dobj_ = calllib('matctrl', 'ml_random_number_distribution_new');

            switch d
                case randomdistribution.UniformInt
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_uniform_int_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.UniformReal
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_uniform_real_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                % case randomdistribution.Binomial
                %     validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                %     calllib('matctrl', ...
                %         'ml_binomial_distribution_set', ...
                %         obj.dobj_, ...
                %         varargin{1});

                case randomdistribution.NegativeBinomial
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_negative_binomial_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.Geometric
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_geometric_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1});

                case randomdistribution.Poisson
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_poisson_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1});

                case randomdistribution.Exponential
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_exponential_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1});

                case randomdistribution.Gamma
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_gamma_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.Weibull
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_weibull_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.ExtremeValue
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_extreme_value_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.Normal
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_normal_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.Lognormal
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_lognormal_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.ChiSquared
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_chi_squared_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1});

                case randomdistribution.Cauchy
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_cauchy_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.FisherF
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_fisher_f_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1}, ...
                        varargin{2});

                case randomdistribution.StudentT
                    validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
                    calllib('matctrl', ...
                        'ml_student_t_distribution_set', ...
                        obj.dobj_, ...
                        varargin{1});

                % case randomdistribution.Discrete
                %     obj.dobj_ = calllib('matctrl', ...
                %         'ml_discrete_distribution_set', ...
                %         varargin{:});
                %
                % case randomdistribution.PiecewiseConstant
                %     obj.dobj_ = calllib('matctrl', ...
                %         'ml_piecewise_constant_distribution_set', ...
                %         varargin{:});
                %
                % case randomdistribution.PiecewiseLinear
                %     obj.dobj_ = calllib('matctrl', ...
                %         'ml_piecewise_linear_distribution_set', ...
                %         varargin{:});

            end

            obj.cobj_ = calllib('matctrl', 'ml_random_variable_new', ...
                                cptr, ...
                                obj.dobj_);

            clear('cptr');
        end

        function delete(obj)
            calllib('matctrl', 'ml_random_number_distribution_free', obj.dobj_);
            calllib('matctrl', 'ml_random_variable_free', obj.cobj_);
        end
    end

    % Utility methods.
    methods (Hidden)
        function S = sym(obj)
            %SYM Helper function to allow functionality with sym class
            %functions.
            c = cell(1);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', 'ml_random_variable_name_get', ...
                    obj.cobj_, ...
                    cptr);

            S = symctrl.se2mat(cptr.Value);

            clear('cptr');
        end
    end

    methods
        function r = sample(obj, gen)
            validateattributes(gen, {'randomdevice'}, {'nonempty'});

            r = calllib('matctrl', 'ml_random_variable_sample', ...
                        obj.cobj_, ...
                        gen.cobj_);
        end
    end

    methods
        % function distribution(obj, d, varargin)
        %     validateattributes(d, {'randomdistribution'}, {'nonempty'});
        %
        %     % calllib('matctrl', 'ml_random_number_distribution_free', obj.dobj_);
        %     % obj.dobj_ = calllib('matctrl', 'ml_random_number_distribution_new');
        %
        %     obj.distribution_name = d.name_;
        %
        %     switch d
        %         case randomdistribution.UniformInt
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_uniform_int_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1}, ...
        %                 varargin{2});
        %
        %         case randomdistribution.UniformReal
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_uniform_real_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1}, ...
        %                 varargin{2});
        %
        %         % case randomdistribution.Binomial
        %         %     validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %         %     calllib('matctrl', ...
        %         %         'ml_binomial_distribution_set', ...
        %         %         obj.dobj_, ...
        %         %         varargin{1});
        %
        %         case randomdistribution.NegativeBinomial
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_negative_binomial_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1}, ...
        %                 varargin{2});
        %
        %         case randomdistribution.Geometric
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_geometric_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1});
        %
        %         case randomdistribution.Poisson
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_poisson_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1});
        %
        %         case randomdistribution.Exponential
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_exponential_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1});
        %
        %         case randomdistribution.Gamma
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_gamma_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1}, ...
        %                 varargin{2});
        %
        %         case randomdistribution.Weibull
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_weibull_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1}, ...
        %                 varargin{2});
        %
        %         case randomdistribution.ExtremeValue
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_extreme_value_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1}, ...
        %                 varargin{2});
        %
        %         case randomdistribution.Normal
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_normal_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1}, ...
        %                 varargin{2});
        %
        %         case randomdistribution.Lognormal
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_lognormal_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1}, ...
        %                 varargin{2});
        %
        %         case randomdistribution.ChiSquared
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_chi_squared_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1});
        %
        %         case randomdistribution.Cauchy
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_cauchy_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1}, ...
        %                 varargin{2});
        %
        %         case randomdistribution.FisherF
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             validateattributes(varargin{2}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_fisher_f_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1}, ...
        %                 varargin{2});
        %
        %         case randomdistribution.StudentT
        %             validateattributes(varargin{1}, {'numeric'}, {'nonempty'});
        %             calllib('matctrl', ...
        %                 'ml_student_t_distribution_set', ...
        %                 obj.dobj_, ...
        %                 varargin{1});
        %
        %         % case randomdistribution.Discrete
        %         %     obj.dobj_ = calllib('matctrl', ...
        %         %         'ml_discrete_distribution_set', ...
        %         %         varargin{:});
        %         %
        %         % case randomdistribution.PiecewiseConstant
        %         %     obj.dobj_ = calllib('matctrl', ...
        %         %         'ml_piecewise_constant_distribution_set', ...
        %         %         varargin{:});
        %         %
        %         % case randomdistribution.PiecewiseLinear
        %         %     obj.dobj_ = calllib('matctrl', ...
        %         %         'ml_piecewise_linear_distribution_set', ...
        %         %         varargin{:});
        %
        %     end
        %
        %     % c = cell(1);
        %     % cptr = libpointer('stringPtrPtr', c);
        %     %
        %     % calllib('matctrl', 'ml_random_variable_name_get', ...
        %     %         obj.cobj_, ...
        %     %         cptr);
        %
        %     obj.cobj_ = calllib('matctrl', ...
        %                         'ml_random_variable_distribution_set', ...
        %                         obj.cobj_, ...
        %                         obj.dobj_);
        %
        %     % clear('cptr');
        % end
    end

    % Overloaded operators.
    methods
        % function C = plus(A, B)
        %     %PLUS Overloaded to allow for transfer functions to be added
        %     %without pole-zero cancellations.
        %     C = transferfunction();
        %     if ~isa(A, 'transferfunction')
        %         G = B;
        %         H = A;
        %     else
        %         G = A;
        %         H = B;
        %     end
        %
        %     C.var = G.var;
        %
        %     if ~isa(H, 'transferfunction')
        %         if ~isa(H, 'sym')
        %             H = sym(H);
        %         end
        %
        %         [N, D] = numden(H);
        %         C.num = G.num*D + N*G.den;
        %         C.den = G.den*D;
        %     else
        %         if G.var ~= H.var
        %             error('Transfer functions must have the same variable.');
        %         end
        %         C.num = G.num*H.den + H.num*G.den;
        %         C.den = G.den*H.den;
        %     end
        % end
        %
        % function C = mtimes(A, B)
        %     %MTIMES Overloaded to allow for transfer functions to be
        %     %multiplied without pole-zero cancellations.
        %     C = transferfunction();
        %     if ~isa(A, 'transferfunction')
        %         G = B;
        %         H = A;
        %     else
        %         G = A;
        %         H = B;
        %     end
        %
        %     C.var = G.var;
        %
        %     if ~isa(H, 'transferfunction')
        %         if ~isa(H, 'sym')
        %             H = sym(H);
        %         end
        %
        %         [N, D] = numden(H);
        %         C.num = G.num*N;
        %         C.den = G.den*D;
        %     else
        %         if G.var ~= H.var
        %             error('Transfer functions must have the same variable.');
        %         end
        %         C.num = G.num*H.num;
        %         C.den = G.den*H.den;
        %     end
        % end
        %
        % function C = mrdivide(A, B)
        %     %MRDIVIDE Overloaded to allow for transfer functions to be
        %     %divided without pole-zero cancellations.
        %     C = transferfunction();
        %     if ~isa(A, 'transferfunction')
        %         G = B;
        %         G.num = B.den;
        %         G.den = B.num;
        %         H = A;
        %     else
        %         G = A;
        %         H = B;
        %     end
        %
        %     C.var = G.var;
        %
        %     if ~isa(H, 'transferfunction')
        %         C.num = G.num;
        %         C.den = G.den*H;
        %     else
        %         if G.var ~= H.var
        %             error('Transfer functions must have the same variable.');
        %         end
        %         C.num = G.num*H.den;
        %         C.den = G.den*H.num;
        %     end
        % end
        %
        % function C = mpower(A, B)
        %     %MPOWER Overloaded to allow for transfer functions to use the
        %     %matrix power operator without pole-zero cancellations.
        %     C = transferfunction();
        %     if ~isa(A, 'transferfunction')
        %         G = B;
        %         H = A;
        %     else
        %         G = A;
        %         H = B;
        %     end
        %
        %     C.var = G.var;
        %
        %     if ~isa(H, 'transferfunction')
        %         C.num = G.num^H;
        %         C.den = G.den^H;
        %     else
        %         if G.var ~= H.var
        %             error('Transfer functions must have the same variable.');
        %         end
        %
        %         C.num = G.num^H;
        %         C.den = G.den^H;
        %     end
        % end
    end
end
