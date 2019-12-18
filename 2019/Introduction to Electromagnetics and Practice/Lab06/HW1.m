clear all;
clc;

%% values

d_sam=5;
plot_mag=2;

a=5;        % J영역의 x 위치
b=5;        % J영역은 y=0부터 y=b까지
Jy=2;
Nx=100;
Ny=100;
xup=10;
yup=10;
mu0=1;
dx=xup/Nx;
dy=yup/Ny;

%% Init
Ax = zeros(Ny+1, Nx+1); % but always zeros..
Ay = zeros(Ny+1, Nx+1);
Bz = zeros(Ny+1, Nx+1);

%% Calculate
for i = 2:Nx
    for j = b/dy+2:Ny
        x = (i-1)*dx;
        y = (j-1)*dy;
        
        if i == a/dx+1
            Ay(j, i) = (mu0/pi)*(-0.5*y*log(y^2+(x-5)^2)-x*pi/2-5*atan((x-5)/y)+0.5*(y-5)*log((x-5)^2+(y-5)^2)+x*pi/2+5*atan((x-5)/(y-5))) + 5;
            Bz(j, i) = 0;
        else
            Ay(j, i) = (mu0/pi)*(-0.5*y*log(y^2+(x-5)^2)+x*atan(y/(5-x))-5*atan((x-5)/y)+0.5*(y-5)*log((x-5)^2+(y-5)^2)+x*atan((y-5)/(x-5))+5*atan((x-5)/(y-5))) + 5;
            Bz(j, i) = mu0/pi*(atan(y/(a-x)) + atan((b-y)/(a-x)));
        end
    end
end

%% Plot
x = 0:dx:xup;
y = 0:dy:yup;

subplot(1,2,1);
quiver(x(1:d_sam:Nx+1),y(b/dy+1:d_sam:Ny+1),Ax(b/dy+1:d_sam:Ny+1,1:d_sam:Nx+1),Ay(b/dy+1:d_sam:Ny+1, 1:d_sam:Nx+1), plot_mag)
xlabel('x')
ylabel('y')

subplot(1,2,2);
[X,Y] = meshgrid(x, y);
mesh(X,Y,Bz)
colorbar('v')
colormap('jet')
xlabel('x')
ylabel('y')
xlim([dx xup-dx]);
ylim([b+dy yup-dy]);