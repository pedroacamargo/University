% While Loops
clc, clearvars, close all

z = 100

while z > 75
    disp(sqrt(z));
    z = z - 1;
end

disp("loop ended!");