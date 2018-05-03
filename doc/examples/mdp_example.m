%% MDP Grid World Example
% Example showing the creation of an MDP for the canonical grid world
% example using a nonholonomic robot.

%% Define the Continuous Dynamics
% For this example, we use a nonholonomic robot.
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
% Because the system dynamics are continuous, we need to create a
% discretized space for the MDP to work in. We can either discretize the
% system dynamics, or discretize the state space and interpolate the state
% from the current state of the system.
%
% For this example, we create a 10x10 grid for the x/y coordinates, and
% divide the angle of the nonholonomic robot into an approximate NSEW
% angle.
%
%   N
% W X E
%   S

[X, in, Xf] = dspace(m, sys, {0:10, 0:10, pi/4:pi/2:9*pi/4});

%%
% This discretization creates 400 possible states (10x10x4) for the
% nonholonomic robot to be in.

m.X = X;

%% Create the Inputs
% For this example, we are simulating with very certain inputs. We define
% three possible inputs for the robot: move forward, turn left, and turn
% right.

%%
% Move forward.
m.U{1} = [1, 1];

%%
% Turn left.
m.U{2} = [-pi/4, pi/4];

%%
% Turn right.
m.U{3} = [pi/4, -pi/4];

%% Define the Probability Matrix
% Now that we have defined our inputs, we can propagate the probabilities
% through the matrix.
%
% By default, unless a probability function is provided, we can obtain an
% empty probability matrix directly from the mdp class after defining a
% state matrix and inputs.
%
% However, manually inputting probabilities can be difficult when there are
% more than a small number of states. In our case, there are 160,000
% elements of the probability matrix for each input.
%
% Use |propp| to propagate probabilities according to a pattern for larger
% state spaces.

%%
% The following pattern propagates the probabilities of the nonholonomic
% robot moving forward in the space for all four directions.

pattern = zeros(3, 3, 3);

pattern(:, :, 2) = [0, 0.9, 0; 0.05, NaN, 0.05; 0, 0, 0];
propp(m, [NaN, NaN, 1], 1, pattern);

pattern(:, :, 2) = [0, 0.05, 0; 0.9, NaN, 0; 0, 0.05, 0];
propp(m, [NaN, NaN, 2], 1, pattern);

pattern(:, :, 2) = [0, 0, 0; 0.05, NaN, 0.05; 0, 0.9, 0];
propp(m, [NaN, NaN, 3], 1, pattern);

pattern(:, :, 2) = [0, 0.05, 0; 0, NaN, 0.9; 0, 0.05, 0];
propp(m, [NaN, NaN, 4], 1, pattern);

%%
% Next, we define the pattern for turning left and right. For simplicity,
% we assume that there is a probability of 1 for turns.

pattern = zeros(1, 1, 4);

pattern(:, :, :) = [NaN; 1; 0; 0];
propp(m, [NaN, NaN, 1], 2, pattern);
propp(m, [NaN, NaN, 2], 2, pattern);
propp(m, [NaN, NaN, 3], 2, pattern);
propp(m, [NaN, NaN, 4], 2, pattern);

pattern(:, :, :) = [0; 0; 1; NaN];
propp(m, [NaN, NaN, 1], 3, pattern);
propp(m, [NaN, NaN, 2], 3, pattern);
propp(m, [NaN, NaN, 3], 3, pattern);
propp(m, [NaN, NaN, 4], 3, pattern);

%% Define the Reward Matrix
% From here, we need to define a reward matrix in order to set goals and
% obstacles for the system.
%
% Similar to before, we can obtain an empty reward matrix from the class
% directly, or we can set the rewards using |propr|.

%%
% Let us define a "cliff" that has a penalty for falling off, one or two
% obstacles that we want to avoid, and and a goal, which we want the system
% to reach.

%%
% We start by defining the cliff. We can imagine the cliff on the bottom of
% our state space, and we want a penalty if the nonholonomic robot decides
% to drive off the cliff. To do this, we define a negative reward if the
% robot is facing the cliff and decides to move forward. We could further
% define negative rewards if the robot stays in the region, but the reward
% value typically penalizes actions taken to reach an undesirable state.

pattern = zeros(2, 1, 2);
pattern(:, :, 1) = [NaN; -100];
propr(m, [9, NaN, 3], 1, pattern);

%%
% Next we define an object that we want to avoid. In this case, we define
% the object in the middle of the 10x10 grid at (5, 5), and a small region
% around it that is penalized. Often, when an undesirable state is
% specified, we don't care how the system got to the state, we just wish to
% say that any action that would lead to the state is penalized. In order
% to specify this, use |propr2|.

pattern = zeros(5, 5, 3);
pattern(:, :, 2) = [   0,   0,  -2,   0,   0 ;
                       0,  -2,  -5,  -2,   0 ;
                      -2,  -5, NaN,  -5,  -2 ;
                       0,  -2,  -5,  -2,   0 ;
                       0,   0,  -2,   0,   0 ];

propr2(m, [5, 5, NaN], 1, pattern, 'nanvalue', -10);

%%
% We can also use this method to specify the goal state. We don't
% necessarily care how the system gets to the goal, we just want it to end
% up there. We use a positive reward value to incentivize the system, and
% we place the goal state somewhere on the grid. In our case, we will set
% the goal state at (1, 10).

propr2(m, [1, 10, NaN], 1, NaN, 'nanvalue', 100);

%%
% We will define another object close to the goal state that we want the
% system to avoid.

propr2(m, {2:3, 8:10, NaN}, 1, NaN, 'nanvalue', -10);

%%
% Now, we should have a reward space that roughly resembles the following:
%
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     1 |     |     |     |     |     |     |     |     |     | 100 |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     2 |     |     |     |     |     |     |     |     | -10 | -10 |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     3 |     |     |     |     |  -2 |     |     |     | -10 | -10 |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     4 |     |     |     |  -2 |  -5 |  -2 |     |     |     |     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     5 |     |     |  -2 |  -5 | -10 |  -5 |  -2 |     |     |     |
% X     +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     6 |     |     |     |  -2 |  -5 |  -2 |     |     |     |     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     7 |     |     |     |     |  -2 |     |     |     |     |     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     8 |     |     |     |     |     |     |     |     |     |     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%     9 |     |     |     |     |     |     |     |     |     |     |
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%    10 | -100| -100| -100| -100| -100| -100| -100| -100| -100| -100|
%       +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
%          1     2     3     4     5     6     7     8     9     10
%                                     Y
%
% where all of the empty spaces have a zero reward.

%%
% As a final step, we specify the discount factor, which has a value that
% is within (0, 1]. The closer to 1 the value is, the further ahead the
% system looks. For this example, we set the discount factor to 0.95.

m.gamma = 0.95;

%% Perform Policy Iteration
% 

%% Simulate the Policy
%

opts = mdpset(m, 'StateFunction', Xf);

[t, y] = mdpsim(sys, m, [0 5], {[2.5, 7.5, pi/2]}, 'MdpOptions', opts);

plot3(y{1}(:, 1), y{1}(:, 2), y{1}(:, 3))
