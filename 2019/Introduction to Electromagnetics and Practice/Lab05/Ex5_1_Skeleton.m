close all;
clear, clc

%% 
a = 2;        % x의 길이
b = 2;        % y의 길이
Nx = 60;      % (Nx+1) x축 방향 격자 개수
Ny = 60;      % (Ny+1) y축 방향 격자 개수
dx = a/Nx;    % x축 간격
dy = b/Ny;    % y축 간격
V0 = 20;
V1 = -10;
V2 = 30;
V3 = -40;
N = 150;      % Summation Number

x = 0:dx:a;
y = 0:dy:b;

%% Initialize(Matrix Allocation)

V = zeros(Ny + 1, Nx + 1);
fn = zeros(Ny + 1, Nx + 1);

for i = 1:Nx+1
    V(1, i) = V3;
end

for i = 1:Nx+1
    V(Ny+1, i) = V1;
end

for j = 1:Ny+1
    V(j, 1) = V2;
end

for j = 1:Ny+1
    V(j, Nx+1) = V0;
end

%% Main loop

for n = 1:N
    if mod(n, 2) == 0
        continue
    end
    
    Cn = (-4)*V2/(n*pi*sinh(n*pi*a/b));
    
    for i = 2:Nx
        for j = 2:Ny
            fn(j, i) = Cn*sinh(n*pi/b*(((i-1)/Nx*a)-a))*sin(n*pi/b*((j-1)/Ny*b));
        end
    end
    
    V = V + fn;
end

for n = 1:N
    if rem(n, 2) == 0
        continue
    end
    
    Cn = (-4)*V1/(n*pi*sinh(n*pi*a/b));
    
    for i = 2:Nx
        for j = 2:Ny
            fn(j, i) = Cn*sinh(n*pi/b*(((i-1)/Nx*a)-a))*sin(n*pi/b*((j-1)/Ny*b));
        end
    end
    
    V = V + rot90(fn, 1);
end

for n = 1:N
    if rem(n, 2) == 0
        continue
    end
    
    Cn = (-4)*V0/(n*pi*sinh(n*pi*a/b));
    
    for i = 2:Nx
        for j = 2:Ny
            fn(j, i) = Cn*sinh(n*pi/b*(((i-1)/Nx*a)-a))*sin(n*pi/b*((j-1)/Ny*b));
        end
    end
    
    V = V + rot90(fn, 2);
end

for n = 1:N
    if rem(n, 2) == 0
        continue
    end
    
    
    Cn = (-4)*V3/(n*pi*sinh(n*pi*a/b));
    
    for i = 2:Nx
        for j = 2:Ny
            fn(j, i) = Cn*sinh(n*pi/b*(((i-1)/Nx*a)-a))*sin(n*pi/b*((j-1)/Ny*b));
        end
    end
    
    V = V + rot90(fn, 3);
end

%% Plot
% Subplot 명령어 이용해서 contour 및 mesh 두가지 플롯 동시에 할 것
% colorbar('v'),  colormap('jet') 명령어 쓸것
% contour plot 등고선 개수는 20개로 할 것

subplot(2,1,1);
[X,Y] = meshgrid(x, y);
contour(X,Y,V,20)
colorbar('v')
colormap('jet')
xlabel('x')
ylabel('y')

subplot(2,1,2);
mesh(X,Y,V)
colorbar('v')
colormap('jet')
xlabel('x')
ylabel('y')