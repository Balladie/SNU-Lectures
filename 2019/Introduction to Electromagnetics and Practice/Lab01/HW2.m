clear all; clc;

% Define x
x = -2*pi:pi/100:2*pi;

% Define sin, cos, tan
y1 = sin(x);
y2 = cos(x);
y3 = tan(x);

figure(1)
% Plot sin(x)
subplot(3, 1, 1);
plot(x, y1)
title('y = sin(x)')
% Plot cos(x)
subplot(3, 1, 2);
plot(x, y2)
title('y = cos(x)')
% Plot tan(x)
subplot(3, 1, 3);
plot(x, y3)
title('y = tan(x)')
axis([-8 8 -2 2])