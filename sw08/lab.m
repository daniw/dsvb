clc;
clear;
close all;

N = 10;
fs = 44100;
load('filter.mat');

X = wavread('music1.wav');
p = X(1:500000)'/max(abs(X(1:500000,1)));

sound(p,fs);

figure(1)
plot(abs(fftshift(fft(p))));
pause(length(p) / fs);

p_ds = downsample(p,N);
sound(p_ds, fs/N);
figure(2);
plot(abs(fftshift(fft(p_ds))));
pause(length(p) / fs / N);

p_lp = conv(p,f);
p_lp_ds = downsample(p_lp,N);
sound(p_lp_ds, fs/N);
figure(3);
plot(abs(fftshift(fft(p_lp_ds))));
