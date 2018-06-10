classdef (SupportExtensionMethods = true) mdp < handle

    properties (Access = protected, Hidden)
        % C Pointer Handle
        cobj_;
    end

    properties (Dependent)
        % Numer of states.
        X
        % Number of inputs.
        U

        % Transition probability matrix.
        P
        % Reward matrix.
        R

        % Discount factor.
        gamma
    end

    methods
        function obj = mdp(varargin)
            validateattributes(varargin, {'cell'}, {'numel', 2});
            validateattributes(varargin{1}, {'numeric'}, ...
                               {'nonnegative', 'scalar'});
            validateattributes(varargin{2}, {'numeric'}, ...
                               {'nonnegative', 'scalar'});

            obj.cobj_ = calllib('matctrl', 'ml_mdp_new', ...
                                varargin{1}, ...
                                varargin{2});
        end

        function delete(obj)
            calllib('matctrl', 'ml_mdp_free', obj.cobj_);
        end
    end

    methods
        % function set.X(obj, n)
        %     validateattributes(n, {'numeric'}, {'scalar'});
        %     calllib('matctrl', 'ml_mdp_num_states_set', obj.cobj_, n);
        % end

        function X = get.X(obj)
            X = calllib('matctrl', 'ml_mdp_num_states_get', obj.cobj_);
        end

        % function set.U(obj, n)
        %     validateattributes(n, {'numeric'}, {'scalar'});
        %     calllib('matctrl', 'ml_mdp_num_inputs_set', obj.cobj_, n);
        % end

        function U = get.U(obj)
            U = calllib('matctrl', 'ml_mdp_num_inputs_get', obj.cobj_);
        end

        % function set.P(obj, s)
        %     x = obj.X;
        %     u = obj.U;
        %     validateattributes(n, {'numeric'}, {'size', [u, x, x]});
        %     calllib('matctrl', 'ml_mdp_probabilities_set', ...
        %             obj.cobj_, ...
        %             s);
        % end
        %
        % function P = get.P(obj)
        %     x = obj.X;
        %     u = obj.U;
        %
        %     P = zeros(u, x, x);
        %
        %     calllib('matctrl', 'ml_mdp_probabilities_get', ...
        %             obj.cobj_, ...
        %             P);
        % end
        %
        % function set.R(obj, s)
        %     x = obj.X;
        %     u = obj.U;
        %     validateattributes(n, {'numeric'}, {'size', [u, x, x]});
        %     calllib('matctrl', 'ml_mdp_rewards_set', ...
        %             obj.cobj_, ...
        %             s);
        % end
        %
        % function R = get.R(obj)
        %     x = obj.X;
        %     u = obj.U;
        %
        %     R = zeros(u, x, x);
        %
        %     calllib('matctrl', 'ml_mdp_rewards_get', ...
        %             obj.cobj_, ...
        %             R);
        % end

        function set.gamma(obj, gamma)
            validateattributes(gamma, {'numeric'}, {'scalar'});
            calllib('matctrl', 'ml_mdp_gamma_set', obj.cobj_, gamma);
        end

        function gamma = get.gamma(obj)
            gamma = calllib('matctrl', 'ml_mdp_gamma_get', obj.cobj_);
        end
    end

    methods
        function varargout = subsref(obj, S)
            if strcmp(S(1).type, '.') && strcmp(S(1).subs, 'P')
                if numel(S) == 1
                    error('Not enough input arguments.');
                elseif ~strcmp(S(2).type, '()')
                    error('Incorrect indexing assignment.');
                end

                idx = S(2).subs;
                x = obj.X;
                u = obj.U;
                nz = calllib('matctrl', 'ml_mdp_probabilities_nnz', ...
                             obj.cobj_, ...
                             idx{1} - 1);

                varargout = cell(1, u);
                a = zeros(nz, 1);
                b = zeros(nz, 1);
                v = zeros(nz, 1);
                aptr = libpointer('ulongPtr', a);
                bptr = libpointer('ulongPtr', b);
                vptr = libpointer('doublePtr', v);

                calllib('matctrl', 'ml_mdp_probabilities_get_sparse', ...
                        obj.cobj_, ...
                        idx{1} - 1, ...
                        aptr, ...
                        bptr, ...
                        vptr);

                a = double(aptr.Value);
                b = double(bptr.Value);
                v = vptr.Value;
                varargout = {sparse(a + 1, b + 1, v, x, x)};

                clear('aptr');
                clear('bptr');
                clear('vptr');

            elseif strcmp(S(1).type, '.') && strcmp(S(1).subs, 'R')
                if numel(S) == 1
                    error('Not enough input arguments.');
                elseif ~strcmp(S(2).type, '()')
                    error('Incorrect indexing assignment.');
                end

                idx = S(2).subs;
                x = obj.X;
                u = obj.U;
                nz = calllib('matctrl', 'ml_mdp_rewards_nnz', ...
                             obj.cobj_, ...
                             idx{1} - 1);

                varargout = cell(1, u);
                a = zeros(nz, 1);
                b = zeros(nz, 1);
                v = zeros(nz, 1);

                calllib('matctrl', 'ml_mdp_rewards_get_sparse', ...
                        obj.cobj_, ...
                        idx{1}, ...
                        a, ...
                        b, ...
                        v);

                varargout = {sparse(a + 1, b + 1, v, x, x)};

            else
                [varargout{1:nargout}] = builtin('subsref', obj, S);
            end
        end

        function obj = subsasgn(obj, S, varargin)
            if strcmp(S(1).type, '.') && strcmp(S(1).subs, 'P')
                if numel(S) > 1
                    idx = S(2).subs;
                else
                    % Reject assignment to entire cell.
                    error('Not enough input arguments.');
                end

                values = varargin{:};

                calllib('matctrl', 'ml_mdp_probabilities_set_sparse', ...
                        obj.cobj_, ...
                        idx{1} - 1, ...
                        numel(values), ...
                        idx{2} - 1, ...
                        idx{3} - 1, ...
                        values);

            else
                obj = builtin('subsasgn', obj, S, varargin{:});
            end
        end
    end
end
