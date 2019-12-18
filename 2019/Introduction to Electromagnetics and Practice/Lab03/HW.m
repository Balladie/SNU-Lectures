close all
clear, clc

%% 변수 통일.

a=8;        % x의 길이
b=2;        % y의 길이
W=2;        % bar의 가로 길이
L=1;        % bar의 세로 길이
Nx=160;      % (Nx+1) x축 방향 격자 개수
Ny=40;      % (Ny+1) y축 방향 격자 개수
dx=a/Nx;    % x축 간격
dy=b/Ny;    % y축 간격
V_hor=0;       % V(1,y) = 2
V_ver=0;       % V(a,y) = 0
V_line=3;
N1=10;
N2=1000;     % Iteration number

%% Initialize (Boundary condition)
V_10 = zeros(Ny + 1, Nx + 1);
V_1000 = zeros(Ny + 1, Nx + 1);

for j = 1:Ny+1
    V_10(j,1) = V_ver;
    V_1000(j,1) = V_ver;
    V_10(j,Nx+1) = V_ver;
    V_1000(j,Nx+1) = V_ver;
end

for i = 1:Nx+1
    V_10(1,i) = V_hor;
    V_1000(1,i) = V_hor;
    V_10(Ny+1,i) = V_hor;
    V_1000(Ny+1,i) = V_hor;
end

for i = 1:Nx+1
    if Nx/2*(1-W/a) <= i && i <= Nx/2*(1+W/a)
        V_10(Ny/2+1,i) = V_line;
        V_1000(Ny/2+1,i) = V_line;
    end
end

for j = 1:Ny+1
    if Ny/2*(1-L/b) <= j && j <= Ny/2*(1+L/b)
        V_10(j,Nx/2+1) = V_line;
        V_1000(j,Nx/2+1) = V_line;
    end
end

x = -a/2:dx:a/2;
y = 0:dy:b;

%% main loop
% V_10
for it = 1:N1
    for j = 2:Ny
        for i = 2:Nx
            if i == Nx/2+1 && Ny/2*(1-L/b) <= j && j <= Ny/2*(1+L/b)
                continue
            end
            if j == Ny/2+1 && Nx/2*(1-W/a) <= i && i <= Nx/2*(1+W/a)
                continue
            end
            V_10(j,i) = (V_10(j,i+1)+V_10(j,i-1)+V_10(j+1,i)+V_10(j-1,i))/4;
        end
    end
end
 
% V_1000
for it = 1:N2
    for j = 2:Ny
        for i = 2:Nx
            if i == Nx/2+1 && Ny/2*(1-L/b) <= j && j <= Ny/2*(1+L/b)
                continue
            end
            if j == Ny/2+1 && Nx/2*(1-W/a) <= i && i <= Nx/2*(1+W/a)
                continue
            end
            V_1000(j,i) = (V_1000(j,i+1)+V_1000(j,i-1)+V_1000(j+1,i)+V_1000(j-1,i))/4;
        end
    end
 end

%% Plot

subplot(2,2,1);
[X,Y] = meshgrid(x, y);
contour(X,Y,V_10,30)
colorbar('v')
colormap('jet')
xlabel('x')
ylabel('y')
title('N = 10')

subplot(2,2,3);
mesh(X,Y,V_10)
colorbar('v')
colormap('jet')
xlabel('x')
ylabel('y')

subplot(2,2,2);
[X,Y] = meshgrid(x, y);
contour(X,Y,V_1000,30)
colorbar('v')
colormap('jet')
xlabel('x')
ylabel('y')
title('N = 1000')

subplot(2,2,4);
mesh(X,Y,V_1000)
colorbar('v')
colormap('jet')
xlabel('x')
ylabel('y')