classdef test_state_space < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here
    properties
        sys
    end

    methods(TestMethodSetup)
        function createStateSpace(testCase)
            % comment
            testCase.sys = statespace();
        end
    end

    methods(Test)
        function testStateSpaceAddStates(testCase)
            syms x1 x2
            sys = testCase.sys;
            sys.states = [x1, x2];

            sys = testCase.sys;
            sys.states = {x1, x2};

            sys = testCase.sys;
            sys.states = {'x1', 'x2'};
        end
        function testStateSpaceGetStates(testCase)
            syms x1 x2
            sys = testCase.sys;
            sys.states = [x1, x2];
        end
        function testStateSpaceSetStates(testCase)
            syms x1 x2
            sys = testCase.sys;
            sys.states = [x1, x2];
        end
        function testStateSpaceNumStates(testCase)
            syms x1 x2
            sys = testCase.sys;
            sys.states = [x1, x2];
        end

        function testStateSpaceAddInputs(testCase)
            syms u1 u2
            sys = testCase.sys;
            sys.inputs = [u1, u2];

            sys = testCase.sys;
            sys.inputs = {u1, u2};

            sys = testCase.sys;
            sys.inputs = {'u1', 'u2'};
        end
        function testStateSpaceGetInputs(testCase)
            syms u1 u2
            sys = testCase.sys;
            sys.inputs = [u1, u2];
        end
        function testStateSpaceSetInputs(testCase)
            syms u1 u2
            sys = testCase.sys;
            sys.inputs = [u1, u2];
        end
        function testStateSpaceNumInputs(testCase)
            syms u1 u2
            sys = testCase.sys;
            sys.inputs = [u1, u2];
        end

        function testStateSpaceAddStateFunctions(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
        function testStateSpaceGetStateFunctions(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
        function testStateSpaceSetStateFunctions(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
        function testStateSpaceNumStateFunctions(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end

        function testStateSpaceAddOutputFunctions(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
        function testStateSpaceGetOutputFunctions(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
        function testStateSpaceSetOutputFunctions(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
        function testStateSpaceNumOutputFunctions(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
    end
end
