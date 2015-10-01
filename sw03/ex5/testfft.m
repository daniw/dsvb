clc;
clear;
close all;

N = 8;
W = exp(-1j*2*pi*[0:N/2-1]/N);
x = fix(128*(rand(N,1)-0.5 + 1j*rand(N,1)-0.5))';
x_cp = x

tic
x = myfft(x);
mytime = toc
tic
xfft = fft(x_cp);
mattime = toc

maxdiff = max(abs(x - xfft))
sumdiff = sum(abs(x - xfft))
mytime / mattime
