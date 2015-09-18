%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DSVB Part 1
% Exercise 2: A/D and D/A Conversion
% Waj, HSLU-T&A
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%% 2.2 Sampling of bandpass signals
clear all;close all;

%% 
% 2. Downsampling
load bpsig;  % signals x1, x2, x3 with fs = 20 kHz and N = 20000 samples 
n = length(x1);
% Determine downsample factor

d = 20; % downsample factor

%Downsample
xd1 = downsample(x1,d);
xd2 = downsample(x2,d);
xd3 = downsample(x3,d);
% plot spectrum of original and downsampled signal
set(figure,'Name','Bandpass Sampling');
hold on; grid on;
% X1
subplot(3,2,1)
plot([-n/2:1:n/2-1],20*log10(abs(fftshift(fft(x1)))));
ylabel('|X_1(f)|_{dB}'); title('\bf{Original Spectra}');
subplot(3,2,2)
plot([-n/2/d:1:n/2/d-1],20*log10(abs(fftshift(fft(xd1)))));
ylabel('|Xd_1(f)|_{dB}'); title('\bf{Downsampled Spectra}');
% X2
subplot(3,2,3)
plot([-n/2:1:n/2-1],20*log10(abs(fftshift(fft(x2)))));
ylabel('|X_2(f)|_{dB}');
subplot(3,2,4)
plot([-n/2/d:1:n/2/d-1],20*log10(abs(fftshift(fft(xd2)))));
ylabel('|Xd_2(f)|_{dB}'); 
% X3
subplot(3,2,5)
plot([-n/2:1:n/2-1],20*log10(abs(fftshift(fft(x3)))));
ylabel('|X_3(f)|_{dB}'); xlabel('f [Hz]');
subplot(3,2,6)
plot([-n/2/d:1:n/2/d-1],20*log10(abs(fftshift(fft(xd3)))));
ylabel('|Xd_3(f)|_{dB}'); xlabel('f [Hz]');

%%
% 3. Correcting the spectrum 
% negation of every 2nd sample value if N is odd

x_orig = xd2; % signal sampled with odd N
corr_f = 1:length(x_orig);
corr_f = (-1).^corr_f;
x_cor = x_orig .* corr_f; % corrected signal

% plot corrected spectrum
set(figure,'Name','Corrected Bandpass Sampling with odd N');
subplot(2,1,1)
plot([-n/2/d:1:n/2/d-1],20*log10(abs(fftshift(fft(x_orig)))));
ylabel('|Xd_2(f)|_{dB}');title('Original spectrum in base band');
subplot(2,1,2)
plot([-n/2/d:1:n/2/d-1],20*log10(abs(fftshift(fft(x_cor)))));
ylabel('|Xd_2(f)|_{dB}');title('Corrected spectrum in base band');


