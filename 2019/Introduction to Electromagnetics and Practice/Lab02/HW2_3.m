%% Initial settings
itMax = 30;

%% plot for Bisection method
subplot(2,1,1);
hold on;

%% Initial settings for Bisection method
a = 1;
b = 5;

%% Find solution w/ Bisection method (stops when 30 iterations finish)
for i=1:itMax
    if (exp(a)-log(a)-a^3-10)*(exp(b)-log(b)-b^3-10) < 0
        c = (a + b) / 2;
        c
        fc = exp(c)-log(c)-c^3-10;
        plot(i, abs(fc), 'r-o')
        
%         if abs(fc) < 10^-3
%             break
%         end
        
        if (exp(a)-log(a)-a^3-10)*fc < 0
            b = c;
        else
            a = c;
        end
    end
end

%% plot for Newton-Raphson method
subplot(2,1,2);
hold on;

%% Initial settings for Newton-Raphson method
p = 6;

%% Find solution w/ Newton-Raphson method (stops when 30 iterations finish)
for i=1:itMax
    fp = exp(p)-log(p)-p^3-10;
    plot(i, abs(fp), 'r-o')
    
%     if fp < 10^-3
%         break
%     end
    
    dfp = exp(p)-1/p-3*p^2;
    p = p - fp/dfp;
    p
end