% close all
clear, clc

%% 값 설정
a = 6;        % the radius for observation
b = 4;        % the radius for the conductor
Nr = 150;             % (Nr+1) r축 방향 격자 개수
Np = 180;             % (Nt+1) phi축 방향 격자 개수
dr = a/Nr;            % rho축 간격
dp = 2*pi/Np;         % phi축 간격
V0 = 3;               
N = 150;            % Summation number

r = 0:dr:a;
p = 0:dp:2*pi;

%% Initialize(Matrix Allocation)

V = zeros(Nr + 1, Np + 1);
fn = zeros(Nr + 1, Np + 1);

for j = 1:Np/4+1
    V(Nr*b/a+1, j) = V0;
end

for j = Np/4+2:Np/2+1
    V(Nr*b/a+1, j) = 0;
end

for j = Np/2+2:Np*0.75+1
    V(Nr*b/a+1, j) = -V0;
end

for j = Np*0.75+2:Np+1
    V(Nr*b/a+1, j) = 0;
end

%% Main loop

for n = 1:N
    if mod(n, 2) == 0
        continue
    end
    
    % 0~180도 V0/2, 나머지 -V0/2
    
    An = 4*(V0/2)/(n*pi*b^n);
    Bn = 4*(V0/2)*b^n/(n*pi);
    
    for i = 1:Nr+1
        if i < Nr*b/a+1
            for j = 1:Np+1
                fn(i, j) = An*(((i-1)*dr)^(n)*sin(n*(j-1)*dp));
            end
        elseif i > Nr*b/a+1
            for j = 1:Np+1
                fn(i, j) = Bn*(((i-1)*dr)^(-n)*sin(n*(j-1)*dp));
            end
        end
    end
    
    V = V + fn;
    
    % 90~270도 -V0/2, 나머지 V0/2
    
    fn = circshift(fn, -Np/4, 2); % rotate -90 degree
    
    for i = 1:Nr+1
        if i == Nr*b/a+1
            continue
        end
        for j = 0.75*Np+2:Np+1
            fn(i, j-1) = fn(i, j);
        end
        fn(i, Np+1) = fn(i, 1);
    end
    
    V = V + fn;
end

%% Plot
% Subplot 명령어 이용해서 contour 및 mesh 두가지 플롯 동시에 할 것
% colorbar('v'),  colormap('jet') 명령어 쓸것
% contour plot 등고선 개수는 20개로 할 것

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