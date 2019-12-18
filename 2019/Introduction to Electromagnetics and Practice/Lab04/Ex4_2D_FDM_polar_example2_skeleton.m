close all
clear, clc

%% ���� ����, voltage ������ V�� define�� ��

rho1=4;             % radius of the outer conductor 
rho0=2;             % radius of the inner conductor 
Nr=160;             % (Nr+1) r�� ���� ���� ����
Np=180;             % (Np+1) phi�� ���� ���� ����
dr=rho1/Nr;         % rho�� ����
dp=2*pi/Np;         % phi�� ����
V2=3;               % �ʱⰪ
V1=-2;              % �ʱⰪ
V0=3;               % �ʱⰪ 
N=5000;             % Iteration number

r = 0:dr:rho1;
p = 0:dp:2*pi;

%% Initialize (Boundary condition)

V = zeros(Nr + 1, Np + 1);

for j = 1:Np+1
    V(1, j) = V0;
end

for j = 1:Np+1
    V(Nr * (rho0 / rho1) + 1, j) = V1;
end

for j = 1:Np+1
    V(Nr + 1, j) = V2;
end
    
%% main loop
% Discontinuity ����ִ� �ڵ嵵 �ݵ�� �־��� ��.

for k=1:N
    for i = 2:Nr
        if i == Nr * (rho0 / rho1) + 1
            continue
        end
        
        for j = 2:Np
            V(i, j) = (V(i-1, j) + V(i+1, j) + (V(i+1, j) - V(i - 1,j))/(2 * i) + (V(i, j-1) + V(i, j+1))/((i * dp)^2))*(2 + 2/((i * dp)^2))^(-1);
        end
        V(i, Np+1) = (V(i-1, j) + V(i+1, j) + (V(i+1, j) - V(i - 1,j))/(2 * i) + (V(i, j-1) + V(i, 2))/((i * dp)^2))*(2 + 2/((i * dp)^2))^(-1);
        V(i, 1) = V(i, Np+1);
    end
end


%% Plot
% Subplot ��ɾ� �̿��ؼ� contour �� mesh �ΰ��� �÷� ���ÿ� �� ��
% colorbar('v'),  colormap('jet') ��ɾ� ����
% contour plot ��� ������ 20���� �� ��

[R,TH] = meshgrid(r, p);
[X,Y] = pol2cart(TH, R);

subplot(2,1,1);
contour(X,Y,transpose(V),20)
colorbar('v')
colormap('jet')

subplot(2,1,2);
mesh(X,Y,transpose(V))
colorbar('v')
colormap('jet')