%% Initial settings
x = 1:0.01:6;
fx = exp(x)-log(x)-x.^3-10;

%% Plot fx
plot(x, fx)