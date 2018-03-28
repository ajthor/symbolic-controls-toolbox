clear, clc

syms m l theta(t) x1 x2 g k

m = 1;
% l = 1;
% k = 1;
g = 9.8;

% sys = eom2symss(-m*l*diff(theta, 2) == -m*g*sin(theta) - k*l*diff(theta), [theta diff(theta)]);
% sys.g(1) = theta;
sys = symss;
sys.states = [x1 x2];
sys.f(1) = x2;
sys.f(2) = -(g/l)*sin(x1) - (k/m)*x2;
sys.g(1) = x1;

sys = linearize(sys);

% lyap(sys)
% lyap(linearize(sys))

%%
% [u,t] = gensig('square',5,30,0.1)
% figure
% lsim(sys|{l==1, k==1}, u, [0 0])

%%
figure
hold on
initial(sys|{l==1, k==1}, [0 5], {[1 0], [3.5 0]});
% initial(sys|{l==1, k==1}, [0 5], {[3 0]});
% initial(sys|{l==1, k==1}, [0 5], {[6 0]});
hold off

% figure
% hold on
% % initial(sys|{l==1, k==1});
% initial(sys|{l==1, k==1}, sym([pi 0]));
% % initial(sys|{l==1, k==1}, sym([2*pi 0]));
% hold off
% 
% figure
% hold on
% initial(sys|{l==1, k==1}, sym([2*pi 0]));
% initial(sys|{l==2, k==1}, sym([2*pi 0]));
% initial(sys|{l==3, k==1}, sym([2*pi 0]));
% hold off
% 
% figure
% hold on
% initial(sys|{l==1, k==1}, sym([2*pi 0]));
% initial(sys|{l==1, k==2}, sym([2*pi 0]));
% initial(sys|{l==1, k==3}, sym([2*pi 0]));
% hold off
