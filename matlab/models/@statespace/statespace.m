classdef (SupportExtensionMethods = true) statespace < handle

    properties (Access = protected, Hidden = true)
        cobj_;
    end

    properties (Dependent)
        states
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
            calllib('matctrl', ...
                    'ml_statespace_states_set', ...
                    obj.cobj_, ...
                    numel(s), ...
                    {s});
        end

        function states = get.states(obj)
            % sz = calllib('matctrl', 'ml_statespace_states_size', obj.cobj_);
            % c = cell(sz, 1);
            % c(:) = {''};

            cptr = libpointer('stringPtrPtr');
            % calllib('matctrl', 'ml_statespace_states_get', obj.cobj_, cptr);
            res = calllib('matctrl', 'ml_statespace_states_get', obj.cobj_);
            disp(res.DataType);
            disp(res.Value);
            states = res.Value;
            clear('res');

            % disp('c value: ')
            % celldisp(c);
            % disp('cptr value: ')
            disp(cptr.Value)

            % states = c;

            states = cptr.Value;
            clear('cptr');
        end
    end

end
