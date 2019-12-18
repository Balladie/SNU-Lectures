close all;
clear, clc

%% 
a = 2;        % x�� ����
b = 2;        % y�� ����
Nx = 60;      % (Nx+1) x�� ���� ���� ����
Ny = 60;      % (Ny+1) y�� ���� ���� ����
dx = a/Nx;    % x�� ����
dy = b/Ny;    % y�� ����
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
% Subplot ��ɾ� �̿��ؼ� contour �� mesh �ΰ��� �÷� ���ÿ� �� ��
% colorbar('v'),  colormap('jet') ��ɾ� ����
% contour plot ��� ������ 20���� �� ��

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