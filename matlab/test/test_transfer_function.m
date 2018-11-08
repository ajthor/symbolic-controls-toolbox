classdef test_transfer_function < matlab.unittest.TestCase
    %UNTITLED6 Summary of this class goes here
    %   Detailed explanation goes here

    methods(Test)
        function testTransferFunctionSetVar(testCase)
            syms s

            sys = transferfunction();
            sys.var = [s];
            testCase.verifyEqual(sys.var, s);

            sys = transferfunction();
            sys.var = {s};
            testCase.verifyEqual(sys.var, s);

            sys = transferfunction();
            sys.var = {'s'};
            testCase.verifyEqual(sys.var, s);
        end
        function testTransferFunctionGetVar(testCase)
            syms s

            sys = transferfunction();
            sys.var = s;

            testCase.verifyEqual(sys.var, s);
        end

        function testTransferFunctionSetNum(testCase)
            syms s

            sys = transferfunction();
            sys.num = [s + 1, s - 1];
            testCase.verifyEqual(sys.num, [s + 1; s - 1]);

            sys = transferfunction();
            sys.num = {s + 1, s - 1};
            testCase.verifyEqual(sys.num, [s + 1; s - 1]);

            sys = transferfunction();
            sys.num = {'s + 1', 's - 1'};
            testCase.verifyEqual(sys.num, [s + 1; s - 1]);
        end
        function testTransferFunctionGetNum(testCase)
            syms s

            sys = transferfunction();
            sys.num = [s + 1, s - 1];

            testCase.verifyEqual(sys.num, [s + 1; s - 1]);
            testCase.verifyEqual(sys.num(1), [s + 1]);
            testCase.verifyEqual(sys.num(2), [s - 1]);
        end

        function testTransferFunctionSetDen(testCase)
            syms s

            sys = transferfunction();
            sys.den = [s + 1, s - 1];
            testCase.verifyEqual(sys.den, [s + 1; s - 1]);

            sys = transferfunction();
            sys.den = {s + 1, s - 1};
            testCase.verifyEqual(sys.den, [s + 1; s - 1]);

            sys = transferfunction();
            sys.den = {'s + 1', 's - 1'};
            testCase.verifyEqual(sys.den, [s + 1; s - 1]);
        end
        function testTransferFunctionGetDen(testCase)
            syms s

            sys = transferfunction();
            sys.den = [s + 1, s - 1];

            testCase.verifyEqual(sys.den, [s + 1; s - 1]);
            testCase.verifyEqual(sys.den(1), [s + 1]);
            testCase.verifyEqual(sys.den(2), [s - 1]);
        end
    end
end
