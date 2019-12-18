clear all; clc;

% ����, ��� �κ� x ���� ������ �� x�� ��ħ
xminus = -2*pi:pi/5:-pi/100;
xplus = pi/100:pi/5:2*pi;
x = [xminus , 0 , xplus];

% y�� Ư������ 1�� ���� �����ϰ� ������ �κ��� sin(pi*t)/(pi*t)�� �����Ͽ� �� �κ��� ��ħ
y = [(sin(pi.*xminus) ./ (pi.*xminus)) , 1 , (sin(pi.*xplus) ./ (pi.*xplus))];

% plot
figure(1)
plot(x, y)