clear all; clc;

% 음수, 양수 부분 x 따로 정의한 뒤 x에 합침
xminus = -2*pi:pi/5:-pi/100;
xplus = pi/100:pi/5:2*pi;
x = [xminus , 0 , xplus];

% y를 특이점만 1로 따로 정의하고 나머지 부분은 sin(pi*t)/(pi*t)로 대입하여 세 부분을 합침
y = [(sin(pi.*xminus) ./ (pi.*xminus)) , 1 , (sin(pi.*xplus) ./ (pi.*xplus))];

% plot
figure(1)
plot(x, y)