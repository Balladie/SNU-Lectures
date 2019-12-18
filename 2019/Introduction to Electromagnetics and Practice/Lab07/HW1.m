clear all;
clc;

%% Setting constants
d_sam=5;
plot_mag=1;

a=4;
b=6;
mu0=1;
mur=2;
xlim=10;
ylim=10;
Nx=100;
Ny=100;
Bext=5;
Bth=pi/4;

dx=xlim/Nx;
dy=ylim/Ny;

%% Initial settings
Bx = zeros(Ny+1, Nx+1);
By = zeros(Ny+1, Nx+1);

for i = 1:a/dx
    for j = 1:Ny+1
        Bx(j, i) = Bext * cos(Bth);
        By(j, i) = -Bext * sin(Bth);
    end
end

for i = b/dx+1:Nx+1
    for j = 1:Ny+1
        Bx(j, i) = Bext * cos(Bth);
        By(j, i) = -Bext * sin(Bth);
    end
end

%% Calculate
for i = a/dx+1:b/dx
    for j = 1:Ny+1
        Bx(j, i) = Bext * cos(Bth);
        By(j, i) = -mur * Bext * sin(Bth);
    end
end

%% Plot
x = 0:dx:xlim;
y = 0:dy:ylim;

quiver(x(1:d_sam:Nx+1),y(1:d_sam:Ny+1),Bx(1:d_sam:Ny+1,1:d_sam:Nx+1),By(1:d_sam:Ny+1, 1:d_sam:Nx+1), plot_mag)
xlabel('x')
ylabel('y')
axis([-2 12 -2 12])