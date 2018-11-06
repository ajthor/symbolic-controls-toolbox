classdef test_statespace < matlab.unittest.TestCase
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
            syms x y u
            sys = testCase.sys;
            sys.states = [x, y];

            sys = testCase.sys;
            sys.states = {x, y};

            sys = testCase.sys;
            sys.states = {'x', 'y'};
        end
        function testStateSpaceGetStates(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
        function testStateSpaceSetStates(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
        function testStateSpaceNumStates(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end

        function testStateSpaceAddInputs(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
        function testStateSpaceGetInputs(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
        function testStateSpaceSetInputs(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
        end
        function testStateSpaceNumInputs(testCase)
            syms x y u
            sys = testCase.sys;
            sys.states = [x y];
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
