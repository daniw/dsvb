clc;
clear;
close all;

a = -2:0.01:2;
t = 3;

figure(1)
title('Rounding in Matlab');

subplot(2,2,1);
plot(a, a, 'g', 'LineWidth', t, a, ceil(a), 'b', 'LineWidth', t);
title('ceil(a)');

subplot(2,2,2);
plot(a, a, 'g', 'LineWidth', t, a, floor(a), 'b', 'LineWidth', t);
title('floor(a)');

subplot(2,2,3);
plot(a, a, 'g', 'LineWidth', t, a, round(a), 'b', 'LineWidth', t);
title('round(a)');

subplot(2,2,4);
plot(a, a, 'g', 'LineWidth', t, a, fix(a), 'b', 'LineWidth', t);
title('fix(a)');

print -dpdf 'round_matlab'
