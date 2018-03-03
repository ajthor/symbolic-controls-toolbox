classdef symtfTest < matlab.unittest.TestCase
    %SYMTFTEST Summary of this class goes here
    %   Detailed explanation goes here
    
    methods (Test)
        function testTransferFunctionCreation(testCase)
            % should be able to create transfer functions using symbolic
            % variables.
            syms s
            G = symtf(1/s);
            testCase.verifyEqual(G.tf, 1/s);
        end
        
        function testTransferFunctionCreation2(testCase)
            % should be able to create transfer functions using
            % coefficients.
            syms s
            G = symtf([1 0], [1 0 0]);
            testCase.verifyEqual(G.tf, 1/s);
            testCase.verifyEqual(G.Numerator, s);
            testCase.verifyEqual(G.Denominator, s^2);
        end
        
        function testAddingTransferFunctions(testCase)
            % should be able to add transfer functions together.
            syms s
            G1 = symtf(1/s);
            G2 = symtf(2/s);
            G3 = G1 + G2;
            testCase.verifyEqual(G3.tf, 3/s);
            testCase.verifyEqual(G3.Numerator, 3*s);
            testCase.verifyEqual(G3.Denominator, s^2);
        end
        
        function testTransferFunctionsWithOtherVariables(testCase)
            % should be able to incorporate other variables into tf.
            syms s a
            G = symtf([1 a], [1 1]);
            testCase.verifyEqual(G.Numerator, s+a);
            testCase.verifyEqual(G.Denominator, s+1);
        end
    end
end

