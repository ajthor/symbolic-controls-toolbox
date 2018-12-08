classdef (SupportExtensionMethods = true, InferiorClasses = {?sym}) randomvar < handle
    %RANDOMVAR Symbolic random variable.

    properties (Access = protected, Hidden)
        % C Pointer Handle
        cobj_;

        % C Pointer Handle for Distribution
        dobj_;
    end

    methods
        function obj = randomvar(varargin)
            validateattributes(varargin, {'cell'}, {'nonempty'});
            validateattributes(varargin{1}, {'char'}, {'nonempty'});
            name = varargin{1};
            if ~isvarname(name)
                error('SYMCTRL::InvalidVariable', 'Invalid variable name.');
            end

            if nargin > 1

            end

            c = symctrl.mat2se(name);
            cptr = libpointer('stringPtrPtr', c);

            obj.dobj_ = calllib('matctrl', 'ml_random_number_distribution_new');
            calllib('matctrl', 'ml_normal_distribution_set', obj.dobj_, 0, 1);

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
