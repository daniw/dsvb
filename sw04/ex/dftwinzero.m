%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DSVB Part 1
% Exercise 5: DFT - Windowing/FFT/Goertzel
% Waj, HSLU-T&A
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%% 5.1 DFT with Windowing and Zero-Padding
clear all; close all;
% <<<== this marks parameters for experimentation  

%% DFT of a harmonic signal with correct measurement interval
fs = 1;
fa = 0.15;
N = 20; % <<<== adjust to correct measurement interval (N should be even)
n = (0:1:N-1);
x1 = cos(2*pi*fa*n/fs);
X1 = fftshift(fft(x1)/N);

set(figure,'Name','DFT Cos'); 
subplot(4,1,1);
plot([0:N-1]*fs/N -fs/2 ,20*log10(abs(X1)),'o-');
axis([-fs/2 (N-1)*fs/2/N -60 0]) 
xlabel('Hz');ylabel('|X| [dB]');title('Correct Measurement Interval');
grid on;

%% DFT with wrong measurement interval
N = 128; % <<<== adjust to wrong measurement interval (N even)
n = (0:1:N-1);
x2 = cos(2*pi*fa*n/fs);
X2=fftshift(fft(x2)/N);

subplot(4,1,2);
plot([0:N-1]*fs/N -fs/2 ,20*log10(abs(X2)),'o-');
axis([-fs/2 (N-1)*fs/2/N -80 0]) 
xlabel('Hz');ylabel('|X| [dB]'); title('Wrong Measurement Interval');
grid on;

%% DFT with wrong measurement interval and zero-padding
Z = N*4; % <<<== total length including zero-padding (Z even)
x3 = [cos(2*pi*fa*n/fs) zeros(1,Z-N)];
X3 = fftshift(fft(x3)/N);

subplot(4,1,3)
plot([0:Z-1]*fs/Z -fs/2 ,20*log10(abs(X3)),'o-');
axis([-fs/2 (Z-1)*fs/2/Z -60 0]) 
xlabel('Hz');ylabel('|X| [dB]'); title('Wrong Measurement Interval with Zero-Padding');
grid on;

%% DFT with wrong measurement interval, zero-padding and windowing
w0 = ones(N,1);       % rectangular window (default)
w1 = chebwin(N,100);  % window function 1 <<<== shape window 1 
w2 = hamming(N);   % window function 2 <<<== shape window 2

x4_0 = [w0'.*cos(2*pi*fa*n/fs) zeros(1,Z-N)]; 
X4_0 = fftshift(fft(x4_0)/N);
x4_1 = [w1'.*cos(2*pi*fa*n/fs) zeros(1,Z-N)]; 
X4_1 = fftshift(fft(x4_1)/N);
x4_2 = [w2'.*cos(2*pi*fa*n/fs) zeros(1,Z-N)]; 
X4_2 = fftshift(fft(x4_2)/N);

subplot(4,1,4);
hold on
plot([0:Z-1]*fs/Z -fs/2 ,20*log10(abs(X4_0)),'o-');
plot([0:Z-1]*fs/Z -fs/2 ,20*log10(abs(X4_1)),'mo-');
plot([0:Z-1]*fs/Z -fs/2 ,20*log10(abs(X4_2)),'ko-');
axis([-fs/2 (Z-1)*fs/2/Z -60 0]) 
xlabel('Hz');ylabel('|X| [dB]'); 
title('Wrong Measurement Interval with Zero-Padding and different Windows');
legend('Rectangular','Chebyshev','Kaiser','Location','NorthEast')
grid on

%% Compare Windowing Functions in Time and Frequency Domain
set(figure,'Name','Windows');
%
subplot(3,2,1); plot(w0); 
axis([1 N 0 1.1]); title('Window 0 - Time Domain'); grid on;
subplot(3,2,2); plot(fftshift(20*log10(abs(fft(w0)))),'o-'); 
axis([1 N -100 50]); title('Window 0 - Frequency Domain'); grid on;
%
subplot(3,2,3); plot(w1); 
axis([1 N 0 1.1]); title('Window 1 - Time Domain'); grid on;
subplot(3,2,4); plot(fftshift(20*log10(abs(fft(w1)))),'mo-'); 
axis([1 N -100 30]); title('Window 1 - Frequency Domain'); grid on;
%
subplot(3,2,5); plot(w2); 
axis([1 N 0 1.1]); title('Window 2 - Time Domain'); grid on;
subplot(3,2,6); plot(fftshift(20*log10(abs(fft(w2)))),'ko-'); 
axis([1 N -100 30]); title('Window 2 - Frequency Domain'); grid on;
