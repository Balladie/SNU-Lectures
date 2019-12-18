X=0:0.01:10;
Y=5.01:0.01:10;

f = zeros(500, 1001);
for i = 1:1001
    for j = 1:500
        x = (i-1)*0.01;
        y = (j+500)*0.01;
        if x == 5
            f(j, i) = -0.5*y*log(y^2+(x-5)^2)-x*pi/2-5*atan((x-5)/y)+0.5*(y-5)*log((x-5)^2+(y-5)^2)+x*pi/2+5*atan((x-5)/(y-5));
        else
            f(j, i) = -0.5*y*log(y^2+(x-5)^2)+x*atan(y/(5-x))-5*atan((x-5)/y)+0.5*(y-5)*log((x-5)^2+(y-5)^2)+x*atan((y-5)/(x-5))+5*atan((x-5)/(y-5));
        end
    end
end

[x,y] = meshgrid(X, Y);
mesh(x,y,f)
colorbar('v')
colormap('jet')
xlabel('x')
ylabel('y')