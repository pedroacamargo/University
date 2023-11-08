% Section 1 - If Statement
% Logic & Loops

clc, clearvars, close all

A = randi(5,1,10000000);
num3_if = sum(A == 3);

tic
if num3_if >= 3
    disp("WOW!")
end
toc

% Section 2 - For Loop
tic
num3 = 0;
for i = 1:length(A)
   if A(i) == 3
    num3 = num3 + 1;
   end
end
toc
if num3 >= 3
    disp("WOW!")
end