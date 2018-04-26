
%% Define the Continuous Dynamics
% For this example, we use a nonholonomic vehicle. 
% 
% We choose the distance between the wheels to be 1, though this is an
% arbitrary selection. If we choose the distance between the wheels to be a
% different value, we need to scale the inputs accordingly.
sys = ctrldemo('nonholonomic');
sys = subs(sys, d, 1);

%% Create a Markov Decision Process
% We create an MDP for the system. 

m = mdp;

%% Discretize the State Space
% Because the system dynamics are
% continuous, we need to create a discretized space for the MDP to work in.
% We can either discretize the system dynamics, or discretize the state
% space and interpolate the state from the current state of the system.
% 
% For this example, we create a 10x10 grid for the x/y coordinates, and
% divide the angle of the nonholonomic robot into an approximate NSEW
% angle.
% 
%   N
% W X E
%   S

[X, in, Xf] = dspace(m, sys, {0:3, 0:3, pi/4:pi/2:9*pi/4});

%%
% This discretization creates 400 possible states (10x10x4) for the
% nonholonomic robot to be in. 

m.X = X;

%% Create the Inputs
% For this example, we are simulating with very certain inputs. We define
% three possible inputs for the robot: move forward, turn left, and turn
% right.

m.U{1} = [1, 1];
% m.U{2} = [-pi/4, pi/4];
% m.U{3} = [pi/4, -pi/4];

%% Define the Probability Matrix
% Now that we have defined our inputs, we can propagate the probabilities
% through the matrix. 
% 
% By default, unless a probability function is provided, we can obtain an
% empty probability and reward matrix directly from the mdp class after
% defining a state matrix and inputs. 
% 
% However, manually inputting probabilities can be difficult when there are
% more than 2 states. Use |propp| to propagate probabilities according to a
% pattern for larger state spaces.

pattern = zeros(3, 3, 3);
pattern(:, :, 2) = [0, 0.9, 0; 0.05, NaN, 0.05; 0, 0, 0];
propp(m, 1, {[NaN, NaN, 1], pattern});
pattern(:, :, 2) = zeros(3, 3);
pattern(:, :, 2) = [0, 0.05, 0; 0.9, NaN, 0; 0, 0.05, 0];
propp(m, 1, {[NaN, NaN, 2], pattern});
pattern(:, :, 2) = zeros(3, 3);
pattern(:, :, 2) = [0, 0, 0; 0.05, NaN, 0.05; 0, 0.9, 0];
propp(m, 1, {[NaN, NaN, 3], pattern});
pattern(:, :, 2) = zeros(3, 3);
pattern(:, :, 2) = [0, 0.05, 0; 0, NaN, 0.9; 0, 0.05, 0];
propp(m, 1, {[NaN, NaN, 4], pattern});

%%
%
% [X, Xf] = dspace(m, sys, {[0, 3, 8, 10], [0, 2, 5], [3, 4, 5]});
% [x1, x2, x3] = ind2sub(size(X), Xf(5, 2, 4))
