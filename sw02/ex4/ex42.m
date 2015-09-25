clc;
clear;
close all;

x = [0 0 1 1 1 0 0 0];

X = fft(x')
Xshift = fftshift(X);

figure(1);
plot(fft(x), '*');
grid
axis([-3.2 3.2 -3.2 3.2]);
