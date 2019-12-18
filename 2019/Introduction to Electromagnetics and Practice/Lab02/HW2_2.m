%% Initial settings
x = 1:0.01:6;
fx = exp(x)-log(x)-x.^3-10;
itMax = 20;

%% plot for Bisection method
subplot(1,2,1);
plot(x, fx)
hold on;

%% Initial settings for Bisection method
a = 1;
b = 5;

%% Find solution w/ Bisection method (Stopping Criterion: abs(f(x)) < 10^-3)
for i=1:itMax
    if (exp(a)-log(a)-a^3-10)*(exp(b)-log(b)-b^3-10) < 0
        c = (a + b) / 2;
        c
        fc = exp(c)-log(c)-c^3-10;
        fc
        plot(c, fc, 'r-o')
        
        if abs(fc) < 10^-3
            break
        end
        
        if (exp(a)-log(a)-a^3-10)*fc < 0
            b = c;
        else
            a = c;
        end
    end
end

%% plot for Newton-Raphson method
subplot(1,2,2);
plot(x, fx)
hold on;

%% Initial settings for Newton-Raphson method
p = 6;

%% Find solution w/ Newton-Raphson method (Stopping Criterion: abs(f(x)) < 10^-3)
for i=1:itMax
    fp = exp(p)-log(p)-p^3-10;
    plot(p, fp, 'r-o')
    p
    
    if fp < 10^-3
        break
    end
    
    dfp = exp(p)-1/p-3*p^2;
    p = p - fp/dfp;
end