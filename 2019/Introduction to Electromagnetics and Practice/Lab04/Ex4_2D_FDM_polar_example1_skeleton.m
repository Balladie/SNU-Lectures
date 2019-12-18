close all
clear, clc

%% ���� ����, voltage ������ V�� define�� ��

rho1=4;             % radius of the conductor 
Nr=100;             % (Nr+1) r�� ���� ���� ����
Np=180;             % (Np+1) phi�� ���� ���� ����
dr=rho1/Nr;         % rho�� ����
dp=2*pi/Np;         % phi�� ����
V0=3;               % �ʱⰪ
V1=5;               % �ʱⰪ
V2=2;               % �ʱⰪ
V3=-1;              % �ʱⰪ
V4=0;               % �ʱⰪ
N=1000;             % Iteration number

r = 0:dr:rho1;
p = 0:dp:2*pi;

%% Initialize (Boundary condition)

V = zeros(Nr + 1, Np + 1);

for j = 1:Np+1
    V(1, j) = V4;
end

for j = 1:Np/4+1
    V(Nr+1, j) = V0;
end

for j = Np/4+2:Np/2+1
    V(Nr+1, j) = V1;
end

for j = Np/2+2:Np*0.75+1
    V(Nr+1, j) = V2;
end

for j = Np*0.75+2:Np+1
    V(Nr+1, j) = V3;
end

%% main loop

for k=1:N
    for i = 2:Nr
        V(i, 1) = (V(i-1, 1) + V(i+1, 1) + (V(i+1, 1) - V(i - 1,1))/(2 * i) + (V(i, Np) + V(i, 2))/((i * dp)^2))*(2 + 2/((i * dp)^2))^(-1);
        V(i, Np+1) = V(i, 1);
        for j = 2:Np
            V(i, j) = (V(i-1, j) + V(i+1, j) + (V(i+1, j) - V(i - 1,j))/(2 * i) + (V(i, j-1) + V(i, j+1))/((i * dp)^2))*(2 + 2/((i * dp)^2))^(-1);
        end
    end
end

%% Plot -> pol2cart��ɾ� �̿��Ұ�
% Subplot ��ɾ� �̿��ؼ� contour �� mesh �ΰ��� �÷� ���ÿ� �� ��
% colorbar('v'),  colormap('jet') ��ɾ� ����
% contour plot ��� ������ 20���� �� ��

[R,TH] = meshgrid(r, p);
[X,Y] = pol2cart(TH, R);

subplot(2,1,1);
contour(X,Y,transpose(V),21)
colorbar('v')
colormap('jet')

subplot(2,1,2);
mesh(X,Y,transpose(V))
colorbar('v')
colormap('jet')