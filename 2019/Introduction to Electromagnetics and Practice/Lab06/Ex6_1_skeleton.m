clear all;
clc;

b=1;                    %반지름
L=2;                    %원기둥 높이
mu0=1;                  %permeability
Nx=60;
Ny=60;
xlim=3;
ylim=3;
dx=xlim*2/Nx;
dy=ylim*2/Ny;
p=20-L/2;
M0=50;
Bx_ext=0.001;

Mt = pi*b*b*L*M0;

B_ind_R=zeros(Ny+1,Nx+1);           %자회된 물질에 의해 만들어진 B field의 R성분
B_ind_th=zeros(Ny+1,Nx+1);          %자회된 물질에 의해 만들어진 B field의 theta성분
B_ind_x=zeros(Ny+1,Nx+1);           %자회된 물질에 의해 만들어진 B field의 x성분
B_ind_y=zeros(Ny+1,Nx+1);           %자회된 물질에 의해 만들어진 B field의 y성분

for j = 1:Ny+1
    for i = 1:Nx+1
        x = (i-Nx/2-1)*xlim/(Nx/2);
        y = (j-Ny/2-1)*ylim/(Ny/2);
        R = sqrt(x^2 + y^2 + p^2);
        K = mu0*Mt/(4*pi*R^3);
        cos_th = p/R;
        sin_th = sqrt(x^2+y^2) / R;
        
        if x==0 && y==0
            cos_ph = 0;
            sin_ph = 0;
        else
            cos_ph = x / sqrt(x^2+y^2);
            sin_ph = y / sqrt(x^2+y^2);
        end
        
        B_ind_R(j, i) = K*2*cos_th;
        B_ind_th(j, i) = K*sin_th;
        
        B_ind_x(j, i) = B_ind_R(j, i)*sin_th*cos_ph + B_ind_th(j, i)*cos_th*cos_ph;
        B_ind_y(j, i) = B_ind_R(j, i)*sin_th*sin_ph + B_ind_th(j, i)*cos_th*sin_ph;
    end
end

Bx=zeros(Ny+1, Nx+1);                  %total B field의 x성분
By=zeros(Ny+1, Nx+1);                  %total B field의 y성분

Bx = B_ind_x + Bx_ext;
By = B_ind_y;

x = -xlim:dx:xlim;
y = -ylim:dy:ylim;

% Plot
quiver(x(1:3:Nx+1),y(1:3:Ny+1),Bx(1:3:Ny+1,1:3:Nx+1),By(1:3:Ny+1, 1:3:Nx+1),2)