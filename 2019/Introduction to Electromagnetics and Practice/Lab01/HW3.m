clear all;
clc;

% �ʱ� ���� - 30*30 ���� ���� �� ���� charge ��ġ
m=30;
A=zeros(m);
B=zeros(m);
Bx=zeros(m);
By=zeros(m);
A(randperm(m,1),randperm(m,1))=1;
e=8.85*10^(-12);

% ���� ��ġ�� charge�� ��ġ ã��
for i=1:m
    for j=1:m
        if (A(i, j) == 1)
            chX = j;
            chY = i;
        end
    end
end

% �� ��ġ������ �������� x �� y ������ ���� Bx, By�� ����
for i=1:m
    for j=1:m
        B(i, j) = 1 ./ (4*pi*e*((j - chX).^2 + (i - chY).^2));
        Bx(i, j) = B(i, j) * ((chX - j) ./ sqrt((j - chX).^2 + (i - chY).^2));
        By(i, j) = B(i, j) * ((chY - i) ./ sqrt((j - chX).^2 + (i - chY).^2));
    end
end

% Plot
figure(1)
subplot(1,2,1);
contour(A)
subplot(1,2,2);
quiver(Bx, By)