classdef symssTest < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testSystemCreation(testCase)
            % define syntax
            syms x1 x2 u1
            sys = symss([x1 x2], u1);
            
            testCase.verifyNumElements(sys.states, 2);
            testCase.verifyNumElements(sys.inputs, 1);
        end
        
        function testNestedStateVariables(testCase)
            % define syntax
            syms x1 x2 x3 u1
            sys = symss;
            sys.states = [x1, [x2, x3]];
            sys.inputs = u1;

            sys.f(1) = x1;
            sys.f(2) = x2 + u1;
            
            testCase.verifyNumElements(sys.states, 3);
            testCase.verifyNumElements(sys.inputs, 1);
        end
        
        function testMatrixParameterCreation(testCase)
            % should be able to pass matrices to constructor.
            sys = symss([1 0; 0 1], [0; 0], [1 0], 0);
            
            testCase.verifyNumElements(sys.states, 2);
            testCase.verifyNumElements(sys.inputs, 0);
        end
        
        function testStateSpaceToTransferFunctionConversion(testCase)
            % should convert transfer function to state space
            sys = symss([0 1 0; 0 0 1; -1 -2 -3], [0; 0; 1], [1 0 0], 0);
            G = symss2symtf(sys);

            sys2 = symtf2symss(G);

            testCase.verifyEqual(sys.A, sys2.A);
        end
    end
end

