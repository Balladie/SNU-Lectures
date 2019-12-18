close all
clear, clc

%% 변수 설정, voltage 분포는 V로 define할 것

rho1=4;             % radius of the outer conductor 
rho0=2;             % radius of the inner conductor 
Nr=160;             % (Nr+1) r축 방향 격자 개수
Np=180;             % (Np+1) phi축 방향 격자 개수
dr=rho1/Nr;         % rho축 간격
dp=2*pi/Np;         % phi축 간격
V2=3;               % 초기값
V1=-2;              % 초기값
V0=3;               % 초기값 
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
% Discontinuity 잡아주는 코드도 반드시 넣어줄 것.

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