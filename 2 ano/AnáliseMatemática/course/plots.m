clc, clearvars, close all


x = linspace(-10, 10);
y1 = (-(x-3).^2) + 10;
y2 = (-(x-3).^2) + 15;
y3 = (-(x-5).^2) + 10;

figure(1);
plot(x,y1);
xlabel('X'),ylabel('Y'),title('Y vs X - Problem A');
grid on

