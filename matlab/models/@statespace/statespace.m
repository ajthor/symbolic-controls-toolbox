classdef (SupportExtensionMethods = true) statespace < handle

    properties (Access = protected, Hidden = true)
        cobj_;
    end

    properties (Dependent)
        states
        inputs
        f
        g
    end

    properties (SetAccess = immutable, Dependent)
        A
        B
        C
        D
    end

    methods
        function obj = statespace(varargin)
            obj.cobj_ = calllib('matctrl', 'ml_statespace_new');
        end

        function delete(obj)
            calllib('matctrl', 'ml_statespace_free', obj.cobj_);
        end
    end

    methods
        function set.states(obj, s)
            validateattributes(s, {'cell', 'char', 'sym'}, {'vector'});
            if ~iscell(s)
                s = {s};
            else
                for k = 1:numel(s)
                    validateattributes(s{k}, {'char'}, {'nonempty'});
                end
            end

            calllib('matctrl', ...
                    'ml_statespace_states_set', ...
                    obj.cobj_, ...
                    numel(s), ...
                    s);
        end

        function states = get.states(obj)
            sz = calllib('matctrl', 'ml_statespace_states_size', obj.cobj_);

            c = cell(1, sz);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_states_get', ...
                    obj.cobj_, ...
                    cptr);

            states = cptr.Value;

            clear('cptr');
        end

        function set.inputs(obj, s)
            validateattributes(s, {'cell', 'char', 'sym'}, {'vector'});
            if ~iscell(s)
                s = {s};
            else
                for k = 1:numel(s)
                    validateattributes(s{k}, {'char'}, {'nonempty'});
                end
            end

            calllib('matctrl', ...
                    'ml_statespace_inputs_set', ...
                    obj.cobj_, ...
                    numel(s), ...
                    s);
        end

        function inputs = get.inputs(obj)
            sz = calllib('matctrl', 'ml_statespace_inputs_size', obj.cobj_);

            c = cell(1, sz);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_inputs_get', ...
                    obj.cobj_, ...
                    cptr);

            inputs = cptr.Value;

            clear('cptr');
        end

        function set.f(obj, s)
            validateattributes(s, {'cell', 'char', 'sym'}, {'vector'});
            if ~iscell(s)
                s = {s};
            else
                for k = 1:numel(s)
                    validateattributes(s{k}, {'char'}, {'nonempty'});
                end
            end

            calllib('matctrl', ...
                    'ml_statespace_f_set', ...
                    obj.cobj_, ...
                    numel(s), ...
                    s);
        end

        function f = get.f(obj)
            sz = calllib('matctrl', 'ml_statespace_f_size', obj.cobj_);

            c = cell(1, sz);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_f_get', ...
                    obj.cobj_, ...
                    cptr);

            f = cptr.Value;

            clear('cptr');
        end

        function set.g(obj, s)
            validateattributes(s, {'cell', 'char', 'sym'}, {'vector'});
            if ~iscell(s)
                s = {s};
            else
                for k = 1:numel(s)
                    validateattributes(s{k}, {'char'}, {'nonempty'});
                end
            end

            calllib('matctrl', ...
                    'ml_statespace_g_set', ...
                    obj.cobj_, ...
                    numel(s), ...
                    s);
        end

        function g = get.g(obj)
            sz = calllib('matctrl', 'ml_statespace_g_size', obj.cobj_);

            c = cell(1, sz);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_g_get', ...
                    obj.cobj_, ...
                    cptr);

            g = cptr.Value;

            clear('cptr');
        end

        function A = get.A(obj)
            n = calllib('matctrl', 'ml_statespace_states_size', obj.cobj_);

            c = cell(1, n^2);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_A_get', ...
                    obj.cobj_, ...
                    cptr);

            A = reshape(cptr.Value, n, n);
        end

        function B = get.B(obj)
            n = calllib('matctrl', 'ml_statespace_states_size', obj.cobj_);
            m = calllib('matctrl', 'ml_statespace_inputs_size', obj.cobj_);

            c = cell(1, n*m);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_B_get', ...
                    obj.cobj_, ...
                    cptr);

            B = reshape(cptr.Value, n, m);
        end

        function C = get.C(obj)
            n = calllib('matctrl', 'ml_statespace_states_size', obj.cobj_);
            p = calllib('matctrl', 'ml_statespace_g_size', obj.cobj_);

            c = cell(1, n*p);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_C_get', ...
                    obj.cobj_, ...
                    cptr);

            C = reshape(cptr.Value, p, n);
        end

        function D = get.D(obj)
            m = calllib('matctrl', 'ml_statespace_inputs_size', obj.cobj_);
            p = calllib('matctrl', 'ml_statespace_g_size', obj.cobj_);

            c = cell(1, m*p);
            cptr = libpointer('stringPtrPtr', c);

            calllib('matctrl', ...
                    'ml_statespace_D_get', ...
                    obj.cobj_, ...
                    cptr);

            D = reshape(cptr.Value, p, m);
        end
    end

end
