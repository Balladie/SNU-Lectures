close all
clear, clc

%% 변수 설정, voltage 분포는 V로 define할 것

Nr=150;
Np=180;
V1=3;
r1=2;
r2=3;
r3=0.2;
N=3000;
dr=r2/Nr;
dp=pi/Np;

r = 0:dr:r2;
p = 0:dp:pi;

%% Initialize (Boundary condition)

V = zeros(Nr + 1, Np + 1);

for i = 1:Nr*(r3/r2)+1
    for j = 1:Np+1
        V(i,j) = V1;
    end
end

for j = 1:Np+1
    V(Nr*(r1/r2)+1, j) = V1*cos(pi/Np*(j-1));
end

%% main loop

for k=1:N
    for i = Nr*(r3/r2)+1:Nr
        if i == Nr*(r1/r2)+1
            continue
        end
        V(i, 1) = (V(i-1, 1) + V(i+1, 1) + (V(i+1, 1) - V(i - 1,1))/(2 * i) + (V(i, 2))/((i * dp)^2))*(2 + 2/((i * dp)^2))^(-1);
        for j = 2:Np
            V(i, j) = (V(i-1, j) + V(i+1, j) + (V(i+1, j) - V(i - 1,j))/(2 * i) + (V(i, j-1) + V(i, j+1))/((i * dp)^2))*(2 + 2/((i * dp)^2))^(-1);
        end
        V(i, Np+1) = (V(i-1, Np+1) + V(i+1, Np+1) + (V(i+1, Np+1) - V(i - 1,Np+1))/(2 * i) + (V(i, Np))/((i * dp)^2))*(2 + 2/((i * dp)^2))^(-1);
    end
    
    % case for i == Nr+1
    V(Nr+1, 1) = (V(Nr, 1) + (0 - V(Nr,1))/(2 * (Nr+1)) + (V(Nr+1, 2))/(((Nr+1) * dp)^2))*(2 + 2/(((Nr+1) * dp)^2))^(-1);
    for j = 2:Np
        V(Nr+1, j) = (V(Nr, j) + 0 + (0 - V(Nr,j))/(2 * (Nr+1)) + (V(Nr+1, j-1) + V(Nr+1, j+1))/(((Nr+1) * dp)^2))*(2 + 2/(((Nr+1) * dp)^2))^(-1);
    end
    V(Nr+1, Np+1) = (V(Nr, Np+1) + 0 + (0 - V(Nr,Np+1))/(2 * (Nr+1)) + (V(Nr+1, Np))/(((Nr+1) * dp)^2))*(2 + 2/(((Nr+1) * dp)^2))^(-1);
end

%% Plot -> pol2cart명령어 이용할것
% Subplot 명령어 이용해서 contour 및 mesh 두가지 플롯 동시에 할 것
% colorbar('v'),  colormap('jet') 명령어 쓸것
% contour plot 등고선 개수는 20개로 할 것

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