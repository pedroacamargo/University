% Logic problems
clc, clearvars, close all

% Parameters
x = linspace(0, 10, 1000000);
y = sin(x);
y_check = 0.5

% Logic
plot(x, y, '.'), hold on, plot([0 10],[y_check y_check],'-r');

y_greater = y > 0.8;
FinalPercent = sum(y_greater) / length(y) * 100