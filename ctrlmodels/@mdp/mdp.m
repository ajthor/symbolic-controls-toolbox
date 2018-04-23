classdef mdp < symss
    %MDP Construct Markov decision process (MDP) or convert system to MDP.
    %
    %   m = MDP creates an empty Markov decision process.
    %
    %   A Markov decision process is characterized by the collection
    %
    %   (X, U, P, R, gamma)
    %
    %   Where X is a set of states, U is a set of actions or controls, P is
    %   the transition probabilities, R is the reward for taking action u
    %   while in state x, and gamma is the discount factor.
    %
    %       The set of states X is characterized by a list of states of the
    %       system and their current values.
    %
    %       The set of allowable inputs U is a list of all possible control
    %       inputs to the system given the state X.
    %
    %       The set of probabilities of selecting an allowable input U in
    %       state X is held in P.
    %
    %       The set of rewards for selecting an allowable input U in state
    %       X is help in R.
    %
    %   In the case of discrete-time systems, the transition probabilities
    %   P : XxUxX -> [0, 1] describe the probability P{x'|x,u} that the
    %   system will transition to state x' given the current state x and
    %   control input u.
    %
    %   In continuous-time systems, the state space must be discretized,
    %   either by creating a discrete system, or by specifying state value
    %   ranges using dspace.
    %
    %   See also mdp/dspace

    % Dependent properties.
    properties (Dependent)
        % Current State
        X
        % Allowable Inputs
        U
        % Transition Probabilities
        P
        % Reward Function
        R

        % Discount Factor
        gamma
        
        % Decision Time
        Td

        % Policy
        policy
    end

    properties (Access = private)
        X_
        U_
        P_
        R_
        
        gamma_
        
        Td_
    end

    % Constructor
    methods
        function obj = mdp(varargin)
            %SYMMDP Construct a Markov decision process.
            ni = nargin;

            % Quick copy.
            if ni == 1 && isa(varargin{1}, 'mdp')
                obj = varargin{1};
                return;
            end

            if ni ~= 0
                if ni == 1
                    arg = varargin{1};
                    obj.states = arg.states;
                    obj.inputs = arg.inputs;
                    obj.f = arg.f;
                    obj.g = arg.g;
                end
            end
        end
    end

    % Getters and setters.
    methods
        function obj = set.X(obj, X)
            % Set the current state for the MDP.
            obj.X_ = X;
        end
        function obj = set.U(obj, U)
            % Set the allowable inputs for the MDP.
            obj.U_ = U;
        end
        function obj = set.P(obj, P)
            % Set the transition probabilities for the MDP.
            obj.P_ = P;
        end
        function obj = set.R(obj, R)
            % Set the reward matrix for the MDP.
            obj.R_ = R;
        end

        function X = get.X(obj)
            X = obj.X_;
        end
        function U = get.U(obj)
            U = obj.U_;
        end
        function P = get.P(obj)
            P = obj.P_;
        end
        function R = get.R(obj)
            R = obj.R_;
        end
    end
end
