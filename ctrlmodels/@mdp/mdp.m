classdef mdp < handle
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
    %   P : X x U x X -> [0, 1] describe the probability P{x'|x,u} that the
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
        % x in X
        X_
        % u in U
        U_@cell
        % P : X x U x X -> [0, 1]
        P_
        % R : X x U x X -> R
        R_
        
        gamma_@double
        
        Td_@double
        
        % pi : X x U -> [0, 1]
        policy_
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
                    if isa(arg, 'symss')
%                         obj.X = arg.states;
                    end
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
%             if ~isa(U{:}, 'sym')
%                 U{:} = sym(U{:});
%             end
            obj.U_ = U;
        end
        
        function obj = set.P(obj, P)
            % Set the transition probabilities for the MDP.
            if ~isscalar(P)
                szX = numel(obj.X_);
                szU = length(obj.U_);
                validateattributes(P, {'numeric'}, ...
                                   {'size', [szX, szX, szU]});
%                 for k = 1:size(P, 1)
%                     if any(sum(P(k, :, :)) ~= 1)
%                         error(['Probabilities in row ', num2str(k), ...
%                                ' do not sum to 1.']);
%                     end
%                 end
            else
                validateattributes(P, {'symfun', 'function_handle'}, ...
                                      {'scalar'});
                args = argnames(P);
                if any(~has([obj.X_], args))
                    error(['Function must have all states ', ...
                           'as parameters.']);
                end
            end
            obj.P_ = P;
        end
        
        function obj = set.R(obj, R)
            % Set the reward matrix for the MDP.
            if ~isscalar(R)
                szX = numel(obj.X_);
                szU = length(obj.U_);
                validateattributes(R, {'numeric'}, ...
                                   {'size', [szX, szX, szU]});
            else
                validateattributes(R, {'symfun', 'function_handle'}, ...
                                      {'scalar'});
                args = argnames(R);
                if any(~has([obj.X_], args))
                    error(['Function must have all states ', ...
                           'as parameters.']);
                end
            end
            obj.R_ = R;
        end
        
        function obj = set.gamma(obj, gamma)
            % Set the discount value for the MDP.
            validateattributes(gamma, {'numeric'}, {'nonnegative', '<', 1});
            obj.gamma = gamma;
        end
        
        function obj = set.policy(obj, policy)
            % Set the policy for the MDP.
            if ~isscalar(policy)
                szX = length(obj.X_);
                szU = length(obj.U_);
                validateattributes(policy, {'numeric'}, ...
                                   {'size', [szX, szU]});
            else
                validateattributes(policy, {'symfun', 'function_handle'}, ...
                                      {'scalar'});
                args = argnames(policy);
                if any(~has([obj.X_], args))
                    error(['Function must have all states ', ...
                           'as parameters.']);
                end
            end
            obj.policy_ = policy;
        end

        function X = get.X(obj)
            X = obj.X_;
        end
        function U = get.U(obj)
            U = obj.U_;
        end
        function P = get.P(obj)
            if isempty(obj.P_)
                if ~isempty(obj.X_) && ~isempty(obj.U_)
                    % If the probability matrix is empty, return a 
                    % size[X, X, U] matrix of zeros.
                    szX = numel(obj.X_);
                    szU = length(obj.U_);
                    P = zeros([szX, szX, szU]);
                else
                    P = double.empty;
                end
            else
                P = obj.P_;
            end
        end
        function R = get.R(obj)
            if isempty(obj.R_)
                if ~isempty(obj.X_) && ~isempty(obj.U_)
                    % If the reward matrix is empty, return a 
                    % size[X, X, U] matrix of zeros.
                    szX = numel(obj.X_);
                    szU = length(obj.U_);
                    R = zeros([szX, szX, szU]);
                else
                    R = double.empty;
                end
            else
                R = obj.R_;
            end
        end
        function p = get.policy(obj)
            if isempty(obj.policy_)
                if ~isempty(obj.X_) && ~isempty(obj.U_)
                    % If the reward matrix is empty, return a size[X, U]
                    % matrix of zeros.
                    szX = numel(obj.X_);
                    szU = length(obj.U_);
                    p = zeros([szX, szU]);
                else
                    p = double.empty;
                end
            else
                p = obj.policy_;
            end
        end
    end
end
