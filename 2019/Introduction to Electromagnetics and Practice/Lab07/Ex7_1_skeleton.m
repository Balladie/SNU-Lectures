clear all;
clc;

Nx=100;     %x���� ���� ����
Ny=100;     %y���� ���� ����
Nt=80;     %�ð� ����
xmax=0.1;   %������ or ����ī�� x���� ũ��
a=0.1;
ymax=0.1;   %������ or ����ī�� y���� ũ��
b=0.1;
dx=xmax/Nx;     %x���� ����
dy=ymax/Ny;     %y���� ����
T=8;
dt=T/Nt;
mu0=1;    %������
R=50;      %����
P=zeros(Nt+1);      %���� ����
V=zeros(Nt+1);      %���� ����
flux = zeros(Nt+1);   %�ڼ�
w=2;      %���ӵ�
h=0.8;      %����
v=0.05;      %�ӵ�
Bz=zeros(Ny+1, Nx+1, Nt+1);     %z���� B����

for i = 1:Nx+1
    for j = 1:Ny+1
        for t_ = 1:Nt+1
            x = (i-1)*dx;
            y = (j-1)*dy;
            t = (t_-1)*dt;
            z = h - v*t;
            
            I0 = 2*cos(w*t);
            
            for j_ = 1:Ny+1
                y_ = dy/2 + (j_-1)*dy;
                Bz(j, i, t_) = Bz(j, i, t_) - mu0*I0/(4*pi)*x*dy/(x^2+(y-y_)^2+z^2)^(1.5);
                Bz(j, i, t_) = Bz(j, i, t_) - mu0*I0/(4*pi)*(a-x)*dy/((x-a)^2+(y-y_)^2+z^2)^(1.5);
            end
            for i_ = 1:Nx+1
                x_ = dx/2 + (i_-1)*dx;
                Bz(j, i, t_) = Bz(j, i, t_) - mu0*I0/(4*pi)*y*dx/((x-x_)^2+y^2+z^2)^(1.5);
                Bz(j, i, t_) = Bz(j, i, t_) - mu0*I0/(4*pi)*(b-y)*dx/((x-x_)^2+(y-b)^2+z^2)^(1.5);
            end
        end
    end
end

for t_ = 1:Nt+1
    for i = 1:Nx+1
        for j = 1:Ny+1
            flux(t_) = flux(t_) + Bz(j, i, t_) * dx * dy;
        end
    end
end

for t_ = 2:Nt+1
    V(t_) = (flux(t_) - flux(t_-1)) / dt;
end

for t_ = 1:Nt+1
    P(t_) = V(t_) * V(t_) / R;
end
        
t = 0:dt:T;
plot(t,P)
xlabel('Time')
ylabel('Power')