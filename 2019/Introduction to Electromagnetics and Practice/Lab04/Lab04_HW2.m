close all
clear, clc

%% ���� ����, voltage ������ V�� define�� ��

Nr=100;
Np=180;
V1=3;
r1=2;
r2=0.2;
N=3000;
dr=r1/Nr;
dp=2*pi/Np;

r = 0:dr:r1;
p = 0:dp:2*pi;

%% Initialize (Boundary condition)

V = zeros(Nr + 1, Np + 1);

for i = 1:Nr*(r2/r1)+1
    for j = 1:Np+1
        V(i, j) = V1;
    end
end

for j = 1:Np+1
    V(Nr+1, j) = V1*cos(2*2*pi/Np*(j-1));
end

%% main loop

for k=1:N
    for i = Nr*(r2/r1)+1:Nr
        for j = 2:Np
            V(i, j) = (V(i-1, j) + V(i+1, j) + (V(i+1, j) - V(i - 1,j))/(2 * i) + (V(i, j-1) + V(i, j+1))/((i * dp)^2))*(2 + 2/((i * dp)^2))^(-1);
        end
        V(i, Np+1) = (V(i-1, Np+1) + V(i+1, Np+1) + (V(i+1, Np+1) - V(i - 1,Np+1))/(2 * i) + (V(i, Np) + V(i, 2))/((i * dp)^2))*(2 + 2/((i * dp)^2))^(-1);
        V(i, 1) = V(i, Np+1);
    end
end

%% Plot -> pol2cart��ɾ� �̿��Ұ�
% Subplot ��ɾ� �̿��ؼ� contour �� mesh �ΰ��� �÷� ���ÿ� �� ��
% colorbar('v'),  colormap('jet') ��ɾ� ����
% contour plot ��� ������ 20���� �� ��

[R,TH] = meshgrid(r, p);
[X,Y] = pol2cart(TH, R);

subplot(1,2,1);
contour(X,Y,transpose(V),20)
colorbar('v')
colormap('jet')

subplot(1,2,2);
mesh(X,Y,transpose(V))
colorbar('v')
colormap('jet')